#include <complex>
#include <iostream>
#include <sys/time.h>
#include <thrust/complex.h>

using namespace std;

__global__ void make_fractal(char *mat, int max_n, int max_row, int max_column){

   int r = threadIdx.x;

   using namespace std;


		for(int c = 0; c < max_column; ++c){
			thrust::complex<float> z;
			int n = 0;

         while(z.real() < 2 && ++n < max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1
				);
			mat[r*max_column + c]=(n == max_n ? '#' : '.');
		}


}

int main(int argc, char *argv[]){
	int max_row, max_column, max_n, print;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;
	print = 0;
	char *mat;
	cudaMallocManaged(&mat, max_row*max_column*sizeof(unsigned char));





   timeval start, end;
   gettimeofday(&start, NULL);

   make_fractal<<<1, max_row>>>(mat, max_n, max_row, max_column);

   cudaDeviceSynchronize();


	gettimeofday(&end, NULL);
   double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
   std::cout << "compute time: " << runtime << " s\n";

   if(print){
      for(int r = 0; r < max_row; ++r){
         for(int c = 0; c < max_column; ++c)
            std::cout << mat[r*max_column + c];
         cout << '\n';
      }
   }
}

