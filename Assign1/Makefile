# DIP Homework Assignment #1
# Date: Mar 7, 2019
# Name: Yu-Ting, TSENG
# ID #: B05902120
# email: b05902120@ntu.edu.tw
# compiled on MacBook (Unix) with g++

All: Warmup Problem1 Problem2

Warmup:
	@echo ============ Warmup ============
	@echo Compiling the code Warmup_a.cpp
	g++ Warmup_a.cpp -o Warmup_a
	@echo  
	@echo Executing the executable file Warmup_a
	./Warmup_a
	@echo --------------------------------
	@echo Compiling the code Warmup_b.cpp
	g++ Warmup_b.cpp -o Warmup_b
	@echo  
	@echo Executing the executable file Warmup_b
	./Warmup_b
	@echo ================================
	@echo  

Problem1:
	@echo =========== Problem1 ===========
	@echo Compiling the code Problem1_a.cpp
	g++ Problem1_a.cpp -o Problem1_a
	@echo  
	@echo Executing the executable file Problem1_a
	./Problem1_a
	@echo --------------------------------
	@echo Compiling the code Problem1_b.cpp
	g++ Problem1_b.cpp -o Problem1_b
	@echo  
	@echo Executing the executable file Problem1_b
	./Problem1_b
	@echo --------------------------------
	@echo Compiling the code Problem1_c.cpp
	g++ Problem1_c.cpp -o Problem1_c
	@echo  
	@echo Executing the executable file Problem1_c
	./Problem1_c
	@echo --------------------------------
	@echo Compiling the code Problem1_d.cpp
	g++ Problem1_d.cpp -o Problem1_d
	@echo  
	@echo Executing the executable file Problem1_d
	./Problem1_d
	@echo --------------------------------
	@echo Compiling the code Problem1_e.cpp
	g++ Problem1_e.cpp -o Problem1_e
	@echo  
	@echo Executing the executable file Problem1_e
	./Problem1_e
	@echo ================================
	@echo  

Problem2: 
	@echo =========== Problem2 ===========
	@echo Compiling the code Problem2_lowfilter.cpp
	g++ Problem2_lowfilter.cpp -o Problem2_lowfilter
	@echo  
	@echo Executing the executable file Problem2_lowfilter
	./Problem2_lowfilter sample4.raw N_1.raw
	@echo --------------------------------
	@echo Compiling the code Problem2_median.cpp and Problem2_outlier.cpp
	g++ Problem2_median.cpp -o Problem2_median
	g++ Problem2_outlier.cpp -o Problem2_outlier
	@echo  
	@echo Executing the executable file Problem2_median and Problem2_outlier
	./Problem2_median sample5.raw tmp.raw
	./Problem2_outlier tmp.raw tmp2.raw
	./Problem2_median tmp2.raw N_2.raw
	@echo ================================
	@echo  

clean: 
	rm -rf *.raw 