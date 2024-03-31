# Haxil Code
This README seeks to divulge the purpose of all of the arduino sketches in this folder to communicate the different patterns one can send to a string of haxils connected in series.
- Reverse_Driver_x5 - Original sketch sent by client, runs 5 motors at the same time. Motors run for a full second every 2 seconds.
- One_At_A_Time - Runs 5 motors in series one at a time. Each motor runs for two seconds every ten seconds.
- Up_And_Down - Runs motors at indices 0, 1, and 2 at the same time. Motors start out at a low intensity and ramp up to a high intensity for 5 seconds and then for the next 5 seconds start at a high intensity and ramp down to a low intensity.
- Three_At_A_Time - Runs motors at indices 0, 1, and 2 at the same time. Motors start out at a low intensity and ramp up to a high intensity for 5 seconds.
- Ramp_Up - Runs 5 motors at the same time. Motors start out at a low intensity and ramp up to a high intensity for 5 seconds.
- Going_Down - Runs 5 motors at the same time. Motors start out at a high intensity and ramp down to a low intensity for 5 seconds.
- Go_Down_Fast - Runs motors at indices 0, 1, and 2. Creates an exponential decay function to make the motor feel like it decreases linearly in intensity by using a builtin arduino Ramp library.
- Fast_Pulses_Based_On_Reverse_Driver - Runs all 5 motors together at quick pulses at 0.1 seconds.
- Fast_Pulses_On_Input - Runs a custom array of motor indices together. All motors use the same ramp function to ramp up and down. Motors start running only after a single character input using the characters 0-9 is allowed to make the motors start running in the ramp pattern.
