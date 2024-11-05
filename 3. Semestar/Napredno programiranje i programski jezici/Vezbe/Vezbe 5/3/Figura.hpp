#ifndef FIGURA_HPP_INCLUDED
#define FIGURA_HPP_INCLUDED

class Figura {
public:
    virtual double obim() const = 0;
    virtual double povrsina() const = 0;
    virtual ~Figura() {}
};

#endif // FIGURA_HPP_INCLUDED