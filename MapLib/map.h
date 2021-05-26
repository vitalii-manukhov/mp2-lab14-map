#pragma once
#include <fstream>
#include "node.cpp"
#include "map_iterator.cpp"

template <class TK, class TV>
class TMap 
{
protected:
    TNode<TK, TV> *mas;
    int size;
    int count;
    void Resize(int newSize);
public:
    TMap(int _size = 1000);
    TMap(const TMap &p);
    TMap(int _size, TNode<TK, TV> *_mas);
    virtual ~TMap();

    int GetCount();
    TNode<TK, TV>* GetMas();

    virtual TV &operator[](TK i);
    virtual TV Find(TK k);
    virtual void Delete(TK k);
    virtual void Add(TK k, TV v);

    typedef TMapIterator<TK, TV> iterator;
    friend class TMapIterator<TK, TV>;
    iterator Begin();

    template <class TTK, class TTV>
    friend std::ostream& operator<<(std::ostream& ostream, const TMap<TTK, TTV>& map);
};


template<class TK, class TV>
void TMap<TK, TV>::Resize(int newSize)
{
  if (newSize > this->size) 
  {
    auto* tmp = new TNode<TK, TV>[newSize];
    for (int i = 0; i < newSize; ++i) 
      tmp[i] = this->mas[i];
    delete[] this->mas;
    this->mas = tmp;
    this->size = newSize;
  }
}

template<class TK, class TV>
TMap<TK, TV>::TMap(int _size)
{
  if (_size <= 0)
    throw "Error";
  this->mas = new TNode<TK, TV>[_size];
  this->size = _size;
  this->count = 0;
}

template<class TK, class TV>
TMap<TK, TV>::TMap(const TMap& p) 
{
  this->size = p.size;
  this->count = p.count;
  this->mas = new TNode<TK, TV>[p.size];
  for (int i = 0; i < p.count; i++)
    this->mas[i] = p.mas[i];
}

template<class TK, class TV>
TMap<TK, TV>::TMap(int _size, TNode<TK, TV>* _mas) 
{
  if (_size <= 0)
    throw "Error";
  this->mas = new TNode<TK, TV>[_size];
  for (int i = 0; i < _size; ++i) 
    this->mas[i] = _mas[i];
  this->count = _size;
}

template<class TK, class TV>
TMap<TK, TV>::~TMap() 
{
  if (this->mas != nullptr)
    delete[] this->mas;
  this->mas = nullptr;
  this->size = 0;
  this->count = 0;
}

template<class TK, class TV>
TV& TMap<TK, TV>::operator[](TK i) 
{
  for (size_t j = 0; j < this->count; j++)
    if (this->mas[j].key == i) 
      return this->mas[j].val;
  this->mas[count].key = i;
  this->mas[count].val = 0;
  this->count++;
  if (this->count == this->size)
    this->Resize(this->size * 2);
  return this->mas[count - 1].val;
}

template<class TK, class TV>
TV TMap<TK, TV>::Find(TK k) 
{
  for (size_t j = 0; j < this->count; j++) 
    if (this->mas[j].key == k) 
      return this->mas[j].val;
  throw "Error";
}

template<class TK, class TV>
void TMap<TK, TV>::Delete(TK k) 
{
  for (size_t j = 0; j < this->count; j++) 
  {
    if (this->mas[j].key == k)
    {
      for (int i = j; i < this->count - 1; ++i) 
        this->mas[i] = this->mas[i + 1];
      break;
    }
  }
}


template<class TK, class TV>
void TMap<TK, TV>::Add(TK k, TV v) 
{
  this->mas[this->count].val = v;
  this->mas[this->count].key = k;
  this->count++;
  if (this->count == size)
    this->Resize(this->size * 2);
}

template<class TK, class TV>
int TMap<TK, TV>::GetCount() 
{
  return this->count;
}

template<class TK, class TV>
TNode<TK, TV>* TMap<TK, TV>::GetMas() 
{
  return this->mas;
}

template<class TK, class TV>
TMapIterator<TK, TV> TMap<TK, TV>::Begin() 
{
  return TMap::iterator(*this);
}

template<class TK, class TV>
std::ostream& operator<<(std::ostream& ostream, const TMap<TK, TV>& map)
{
  for (int i = 0; i < map.count; ++i) 
    ostream << map.mas[i].GetKey() << " " << map.mas[i].GetVal() << "\n";
  return ostream;
}