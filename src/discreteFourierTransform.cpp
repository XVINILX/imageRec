#include <array>
#include <cmath>
#include <complex>
#include <vector>

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */

void dft(std::vector < std::array<float, 4>> projectionProfile, int h) {
	const int projectionsProfileSize = projectionProfile.size();
	int n = 0 ;
	for (int k = 0; k < projectionsProfileSize; k++) {
		n = (k*k) + n;
	}
	

}