from typing import NamedTuple
from random import choice

GROUPS = ['interaction', 'calculation', 'IO']


def closest_devided_by(x, y):
    while x % y != 0:
        x += 1
    return x


class Proces:
    def __init__(self, id, group, counter) -> None:
        self.id = id
        self.group = group
        self.counter = counter

    def __str__(self) -> str:
        return f'ID: {self.id}, Group: {self.group}, Conter: {self.counter}\n'


num_of_int = 5
num_of_cal = 5
num_of_io = 4

lst_of_ints = [Proces(i, 'interaction', 1) for i in range(num_of_int)]
lst_of_cals = [Proces(i, 'calculation', 1) for i in range(num_of_cal)]
lst_of_io = [Proces(i, 'IO', 1) for i in range(num_of_io)]

procs = lst_of_ints + lst_of_cals + lst_of_io
# print(procs)

p_interaction = 0
p_calculation = 0
p_io = 0

for proc in procs:
    if proc.group == 'interaction':
        p_interaction += 1
    if proc.group == 'calculation':
        p_calculation += 1
    if proc.group == 'IO':
        p_io += 1

print(f'Int: {p_interaction}, Cal: {p_calculation}, IO: {p_io}')


if ((p_interaction == 5*p_io and p_calculation == 2*p_io)
    or (p_interaction < 5*p_io and p_calculation < 2*p_io)):
    p_io_time = p_io
    p_interaction_time = p_io_time*5
    p_calculation_time = p_io_time*2
elif p_interaction > 5*p_io and p_calculation <= 2*p_io:
    p_interaction_time = closest_devided_by(p_interaction, 5)
    p_io_time = p_interaction_time // 5
    p_calculation_time = 2*p_io_time
elif p_calculation > 2*p_io and (p_calculation > p_interaction or p_calculation <= p_interaction):
    p_calculation_time = closest_devided_by(p_calculation, 2)
    p_io_time = p_calculation_time // 2
    p_interaction_time = p_io_time * 5


print(f'Int_t: {p_interaction_time}, Cal_t: {p_calculation_time}, IO_t: {p_io_time}')

p_interaction_time -= p_interaction
p_calculation_time -= p_calculation
p_io_time -= p_io
while(p_interaction_time != 0):
    for i in range(len(procs)):
        if procs[i].group == 'interaction':
            procs[i].counter += 1
            p_interaction_time -= 1
            if p_interaction_time == 0:
                break
while(p_calculation_time != 0):
    for i in range(len(procs)):
        if procs[i].group == 'calculation':
            procs[i].counter += 1
            p_calculation_time -= 1
            if p_calculation_time == 0:
                break
while(p_io_time != 0):
    for i in range(len(procs)):
        if procs[i].group == 'IO':
            procs[i].counter += 1
            p_io_time -= 1
            if p_io_time == 0:
                break

p_io_times = 0
p_interaction_times = 0
p_calculation_times = 0
for proc in procs:
    if proc.group == 'interaction':
        p_interaction_times += proc.counter
    elif proc.group == 'calculation':
        p_calculation_times += proc.counter
    elif proc.group == 'IO':
        p_io_times += proc.counter

print(f'Int: {p_interaction_times}, Cal: {p_calculation_times}, IO: {p_io_times}')

