% weight and balance for a cessna 172k with the extended range tanks and a
% basic empty weight of 1550.44

bew = 1445.0;
pilot_front_pass = 0;
rear_pass = 0;
fuel = 0;
bag_a = 0;
bag_b = 0;
stand_atm = 29.92;
taxi_run_time = 0;


prompt = 'What is the Pilot and front passenger weight in lbs? ';
pilot_front_pass = input(prompt)


prompt = 'What is the rear passenger weight in lbs? ';
rear_pass = input(prompt)


prompt = 'What is the amount of fuel in gallons? ';
fuel = input(prompt)


prompt = 'What is the luggage area A weight in lbs? ';
bag_a = input(prompt)


prompt = 'What is the amount of time to taxi in minutes? ';
taxi_run_time = input(prompt)

prompt = 'What is the your estimated fuel burn rate in Gallons per hour? ';
burn_rate = input(prompt)

prompt = 'How long will you be in the air in hours? ';
flight_time = input(prompt)

fuel_weight = fuel .* 6;

arm_bew = 41.2;
arm_pilot_front_pass = 36.0;
arm_rear_pass = 70.0;
arm_fuel = 48.0;
arm_bag_a = 95.0;


ramp_weight = bew + pilot_front_pass + rear_pass + fuel_weight + bag_a;

mom_bew = arm_bew .* bew;
mom_pilot = arm_pilot_front_pass .* pilot_front_pass;
mom_rear_pass = arm_rear_pass .* rear_pass;
mom_fuel = arm_fuel .* fuel_weight;
mom_bag_a = arm_bag_a .* bag_a;


ramp_moment = mom_bew + mom_pilot + mom_rear_pass + mom_fuel + mom_bag_a;

ramp_arm = ramp_moment ./ ramp_weight;



taxi_run_weight = (taxi_run_time ./ 60) .* 6;
mom_taxi_run = taxi_run_weight .* arm_fuel;
takeoff_mom = ramp_moment - mom_taxi_run;
takeoff_weight = ramp_weight - taxi_run_weight
takeoff_cg = takeoff_mom ./ takeoff_weight

syms x
y = piecewise(x<35 , 0 , 35<x<41.0 , (x*100)-1550 , 38.5<x<47.25 , 2550 , x>47.25 , 0);
fplot(y)
hold on
syms p
t = piecewise(p<35 , 0 , 35<p<35.5 , (p*100)-1550 , 35.5<p<40.5 , 2000 , p>40.5 , 0);
fplot(t)
title('Center of Gravity Limits')
xlabel('Inches Aft of Datum')
ylabel('Loaded Airplane Weight [lbs]')
annotation('textbox', [0.25, 0.2, 0.1, 0.1], 'String', "Utility Catagory")
annotation('textbox', [0.6, 0.2, 0.1, 0.1], 'String', "Normal Catagory")
annotation('textbox', [0.14, 0.8, 0.1, 0.1], 'String', "Outside of limits")
xlim([34, 49])
ylim([1500, 2600])

plot(takeoff_cg, takeoff_weight, 'r*');




%usable fuel for the cessna 172 with the extended tanks is 50 gallons and
%the total fuel is 54 gallons. 
usable_fuel = fuel - 4;
time_to_empty = usable_fuel ./ burn_rate





fuel_usage = flight_time .* burn_rate

%fuel weighs 6lbs per gallon
landing_weight = takeoff_weight - (fuel_usage .* 6)
mom_landing = takeoff_mom - ((fuel_usage .* 6) .* arm_fuel);
landing_cg = mom_landing ./ landing_weight

plot(landing_cg, landing_weight, 'b*');

legend('Normal','Utility','Take-off','Landing')




