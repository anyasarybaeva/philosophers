# philosophers
## Final mark
<img width="205" alt="Снимок экрана 2022-04-22 в 00 58 21" src="https://user-images.githubusercontent.com/36243405/164567281-56ca39db-6ccb-4856-bfb1-efb2ade8acb5.png">

---
## Mandatory part
Program should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
* number_of_philosophers: The number of philosophers and also the number of forks.
* time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
* time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
* number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
