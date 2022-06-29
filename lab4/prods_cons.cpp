#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <ctime>

#define MAGAZINE_PATH "magazine.txt"

using namespace std;

class monitor {
private:
    int size;
    int items;
    pthread_cond_t full;
    pthread_cond_t empty;
    pthread_mutex_t condlock;

public:
    monitor()
    {
        size = 10;
        items = check_magazine();
        pthread_cond_init(&full, NULL);
        pthread_cond_init(&empty, NULL);
        pthread_mutex_init(&condlock, NULL);
    }

    int check_magazine()
    {
        string items;
        fstream fp(MAGAZINE_PATH);
        if (fp.is_open())
        {
            getline (fp, items);
            fp.close();
            return stoi(items);
        }
        else
            throw invalid_argument("No file named " MAGAZINE_PATH);
    }

    void update_magazine(int value)
    {
        fstream fp(MAGAZINE_PATH);
        if (fp.is_open())
        {
            fp << value;
            fp.close();
            items = value;
        }
        else
            throw invalid_argument("No file named " MAGAZINE_PATH);

    }

    int get_items()
    {
        return items;
    }

    void set_size(int s)
    {
        size = s;
    }

    int get_size()
    {
        return size;
    }

    void enter(int n)
    {
        pthread_mutex_lock(&condlock);
        if (items + n >= size)
            pthread_cond_wait(&full, &condlock);

        if (items + n <= size)
            update_magazine(items+n);

        if (items > 0)
            pthread_cond_signal(&empty);

        pthread_mutex_unlock(&condlock);
    }

    void remove(int n)
    {
        pthread_mutex_lock(&condlock);
        if (items - n < 0)
            pthread_cond_wait(&empty, &condlock);

        if (items - n >= 0)
           update_magazine(items-n);

        if (items < size)
            pthread_cond_signal(&full);

        pthread_mutex_unlock(&condlock);
    }
} M;

string get_current_time()
{
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    stringstream o_stream;
    o_stream << setw(2) << setfill('0')
         << (now->tm_hour) << ':'
         << setw(2) << setfill('0')
         << (now->tm_min) << ':'
         << setw(2) << setfill('0')
         << now->tm_sec;
    string output = o_stream.str();
    return output;
}

void append_txt(string path, string text)
{
    fstream fp(path, std::ios_base::app | std::ios_base::in);
    if (fp.is_open())
        fp << text << endl;
    else
        throw invalid_argument("No file named " + path);
}


struct args {
    int min_n;
    int max_n;
    string log_path;
};

void *producer(void *input)
{
    int n;
    int min_n = ((struct args*)input)->min_n;
    int max_n = ((struct args*)input)->max_n;
    string log_path = ((struct args*)input)->log_path;
    string text;
    while (1)
    {
        srand(time(NULL));
        n = rand()%(max_n-min_n+1)+min_n;
        text = "(" + get_current_time() + ")" + " Trying to produce " + to_string(n) + " items.\n";
        append_txt(log_path, text);
        M.enter(n);
        text = "(" + get_current_time() + ")" + " Produced " + to_string(n) + " items.\n";
        append_txt(log_path, text);
        sleep(1);
    }
}

void *consumer(void *input)
{
    int n;
    int min_n = ((struct args*)input)->min_n;
    int max_n = ((struct args*)input)->max_n;
    string log_path = ((struct args*)input)->log_path;
    string text;
    while (1)
    {
        srand(time(NULL));
        n = rand()%(max_n-min_n+1)+min_n;
        text = "(" + get_current_time() + ")" + " Trying to comsume " + to_string(n) + " items.\n";
        append_txt(log_path, text);
        M.remove(n);
        text = "(" + get_current_time() + ")" + " Consumed " + to_string(n) + " items.\n";
        append_txt(log_path, text);
        sleep(1);
    }
}


int main(int argc, char** argv){
    if (argc != 8)
    {
        cerr << "Usage: ./prods_cons SIZE N_PRODUCERS N_CONSUMERS MIN_N_PRODUCER MAX_N_PRODUCER MIN_N_CONSUMER MAX_N_CONSUMER\n";
        return 1;
    }
    int num_of_producers = atoi(argv[2]);
    int num_of_consumers = atoi(argv[3]);

    pthread_t p[num_of_producers], c[num_of_consumers];

    M.set_size(atoi(argv[1]));

    for (int i = 0; i < num_of_producers; i++)
    {
        struct args *producer_args = (struct args *)malloc(sizeof(struct args));
        producer_args->min_n = atoi(argv[4]);
        producer_args->max_n = atoi(argv[5]);
        string log_path = "producer" + to_string(i) + ".txt";
        producer_args->log_path = log_path;

        std::ofstream ofs;
        ofs.open(log_path, std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        pthread_create(&p[i], NULL, &producer, (void *)producer_args);

    }
    for (int i = 0; i < num_of_consumers; i++)
    {
        struct args *consumer_args = (struct args *)malloc(sizeof(struct args));
        consumer_args->min_n = atoi(argv[6]);
        consumer_args->max_n = atoi(argv[7]);
        string log_path = "consumer" + to_string(i) + ".txt";
        consumer_args->log_path = log_path;

        std::ofstream ofs;
        ofs.open(log_path, std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        pthread_create(&c[i], NULL, &consumer, (void *)consumer_args);

    }

    for (int i = 0; i < num_of_producers; i++) {
        pthread_join(p[i], NULL);
    }
    for (int i = 0; i < num_of_consumers; i++) {
        pthread_join(c[i], NULL);
    }

    return 0;
}