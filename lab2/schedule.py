GROUP_IO = 0
GROUP_CALC = 1
GROUP_INT = 2
GROUP_COUNTER = 3

current_group = GROUP_CALC

# ... | 0 1 1 2 2 2 2 | 0 1 1 2 2 2 2 | 0 1 1 2 2 2 | ...

counter_io = 1
counter_calc = 2
counter_int = 4


q_io = 1
q_calc = 1
q_int = 0
q = [0, 0, q_io, q_calc, q_int]

def get_q(group):
    return group + 2

while True:
    if current_group == GROUP_IO :
        current_group = GROUP_CALC

        counter_io = 1

    if current_group == GROUP_CALC and counter_calc == 0:
        current_group = GROUP_INT
        counter_calc = 2

    elif current_group == GROUP_CALC and counter_calc != 0:
        counter_calc -= 1
    if current_group == GROUP_INT and counter_int == 0:
        current_group = GROUP_IO
        counter_int = 4
    elif current_group == GROUP_INT and counter_int != 0:
        counter_int -= 1

    for i in range(3):
        new_group = (current_group + i) % GROUP_COUNTER
        if q[get_q(new_group)] == 1:
            current_group = new_group
            break

    print(current_group)
