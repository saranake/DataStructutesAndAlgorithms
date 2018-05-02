#include <iostream>
#include <vector>


void swap(std::vector<int> &v, int i, int j)
{
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void
partition (std::vector<int> &v, int l, int r, int &p1, int &p2) {

  int p;
  p = v[0];

  int i = l;
  int lt = l;
  int gt = r;


  while (gt >= i) {

    if(v[i] < p) {
      swap(v, i, lt); 
      i++;
      lt++;
    } else if (v[i] > p) {
      swap(v, i, gt); 
      gt--;
    } else if(v[i]  == p) {
      i++;
    }
  }

  p1 = lt;
  p2 = gt ;
}

int main()
{
  int p1, p2;
  int c;
  std::cin >> c;
  std::vector<int> v(c);
  
  for(int i = 0; i < c; i++) {
    std::cin >> v[i];
  }
  partition(v, 0, c-1, p1, p2);

  for(int i = 0; i < c; i++) {
    std::cout  << v[i] << " ";
  }
  std::cout << std::endl;
  std::cout  << p1 << " " << p2 << " " << std::endl;
  
}
