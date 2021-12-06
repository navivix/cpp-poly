#include <iostream>
#include <math.h>

using namespace std;

class poly
{
private:
  int stage;
  double *coefficients;

public:
  poly(double coeff = 0)
  {
    coefficients = new double[1];
    stage = 0;
    coefficients[0] = coeff;
  }

  ~poly()
  {
    delete[] coefficients;
  }

  poly(const poly &old)
  {
    stage = old.stage;
    coefficients = new double[old.stage + 1];
    for (int i = 0; i <= stage; i++)
    {
      coefficients[i] = old.coefficients[i];
    }
  }

  poly &operator=(const poly &rhs)
  {
    stage = rhs.stage;
    delete[] coefficients;
    coefficients = new double[stage + 1];
    for (int i = 0; i <= stage; i++)
    {
      coefficients[i] = rhs.coefficients[i];
    }
    return *this;
  }

  double operator()(double x) const
  {
    double res = 0;
    for (int i = stage; i >= 0; i--)
    {
      res += coefficients[i] * pow(x, i);
    }
    return res;
  }

  double &operator[](int s)
  {
    if (s > stage)
    {
      double *n = new double[s + 1];
      for (int i = 0; i <= stage; i++)
      {
        n[i] = coefficients[i];
      }
      for (int i = stage + 1; i <= s; i++)
      {
        n[i] = 0;
      }
      delete[] coefficients;
      coefficients = n;
      stage = s;
    }
    return coefficients[s];
  }

  friend poly operator+(const poly &, const poly &);
  friend poly operator*(const poly &, const poly &);
  friend poly operator*(double, const poly &);
  friend ostream &operator<<(ostream &, const poly &);
};

poly operator+(const poly &lhs, const poly &rhs)
{
  poly n;
  for (int i = 0; i <= lhs.stage; i++)
  {
    n[i] += lhs.coefficients[i];
  }
  for (int i = 0; i <= rhs.stage; i++)
  {
    n[i] += rhs.coefficients[i];
  }
  return n;
}

poly operator*(const poly &lhs, const poly &rhs)
{
  poly n;
  if (lhs.stage && rhs.stage)
  {
    for (int i = 0; i <= lhs.stage; i++)
    {
      for (int j = 0; j <= rhs.stage; j++)
      {
        n[i + j] += lhs.coefficients[i] * rhs.coefficients[j];
      }
    }
  }
  return n;
}

poly operator*(double multiplier, const poly &p)
{
  poly n;
  if (multiplier)
  {
    n = p;
    for (int i = 0; i <= n.stage; i++)
    {
      n.coefficients[i] *= multiplier;
    }
  }
  return n;
}

ostream &operator<<(ostream &out, const poly &p)
{
  if (p.stage)
  {
    for (int i = p.stage; i >= 0; i--)
    {
      if (p.coefficients[i])
      {
        out << p.coefficients[i];
        if (i != 0)
          out << "x";
        if (i > 1)
          out << "^" << i;
        if (i != 0)
          out << " + ";
      }
    }
  }
  else
  {
    out << 0;
  }
  return out;
}