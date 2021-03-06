#pragma once
#ifdef __cplusplus
extern "C" {
#include <stdlib.h>
#include "simlib.h"
#endif

#ifdef __cplusplus
}
#endif

#include<fstream>
#include<string>
#include <iostream>
#include <iomanip>  

using namespace std;
namespace utils {
	class FileIO {
	private:
		string FileName;
		ofstream OUT;
	public:
		inline FileIO(const string& name, const int mode) :
			FileName(name)
		{
			OUT.open(name, mode);
		}

		inline ~FileIO()
		{
			OUT.close();
		}

		template <typename T>
		inline void fprint(T data)
		{
			cout << "warning \n";
			OUT << data << "\n";
		}

		template <>
		inline void fprint(Simulation_Run_Data_Ptr data)
		{
			OUT << std::fixed<< PACKET_ARRIVAL_RATE+0.00000001 << "\t";
			OUT << std::fixed <<1e3 * data->accumulated_delay / ( data->arrival_count - data->number_of_packets_processed)<< "\n";
		}
	};
	
	//N : begin
	//M : end
	//K : num of sample
	template<int N, int M, int K>
	constexpr auto sample{ []() constexpr {
		constexpr size_t size = K;
		constexpr double interval = (double)(M - N) / (double)K;
		std::array<double, K> result{};
		for (int i = 0; i < size; ++i)
		{
			result[i] = (i+1) * interval;
		}
		return result;
		}()
	};

}