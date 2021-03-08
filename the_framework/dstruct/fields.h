#ifndef FIELDS_H
#define FIELDS_H

#include <initializer_list>

namespace Datastructures{

/**
 * Start - End (first out of bounds)
 */
template<typename I> struct field_se_st{
  I start{0};
  I end{0};
  field_se_st()=default;
  field_se_st& operator=(std::initializer_list<I> il){
    auto it = il.begin();
    start = *it;
    ++it;
    end = *it;
    return *this;
  }
};
template<typename I> using field_se = struct field_se_st<I>;

/**
 * Start - Length
 */
template<typename I> struct field_sl_st{
  I start{0};
  I length{0};
  field_sl_st()=default;
  field_sl_st& operator=(std::initializer_list<I> il){
    auto it = il.begin();
    start = *it;
    ++it;
    length = *it;
    return *this;
  }
};
template<typename I> using field_sl = struct field_sl_st<I>;

/**
 * First - Last (Index)
 */
template<typename I> struct field_fl_st{
  I first{0};
  I last{0};
  field_fl_st()=default;
  field_fl_st& operator=(std::initializer_list<I> il){
    auto it = il.begin();
    first = *it;
    ++it;
    last = *it;
    return *this;
  }
};
template<typename I> using field_fl = struct field_fl_st<I>;

//----- Generate Start - End (first out of bounds)

template<typename I> constexpr field_se<I> make_field_se(I const _s, I const _e){
 field_se<I> res;
  res = {_s,_e};
  return res;
}

template<typename I> constexpr field_se<I> make_field_se(field_sl<I> const fsl){
  return make_field_se<I>(fsl.start,fsl.start+fsl.length);
}

template<typename I> constexpr field_se<I> make_field_se(field_fl<I> const ffl){
  return make_field_se<I>(ffl.first,ffl.last+1);
}

//----- Generate Start - Length

template<typename I> constexpr field_sl<I> make_field_sl(I const _s, I const _l){
  field_sl<I> res;
  res = {_s,_l};
  return res;
}

template<typename I> constexpr field_sl<I> make_field_sl(field_se<I> const fse){
  return make_field_sl<I>(fse.start,fse.end-fse.start);
}

template<typename I> constexpr field_sl<I> make_field_sl(field_fl<I> const ffl){
  return make_field_sl<I>(ffl.first,(ffl.last-ffl.first)+1);
}

//----- Generate First - Last (Index)

template<typename I> constexpr field_fl<I> make_field_fl(I const _f, I const _l){
  field_fl<I> res;
  res = {_f,_l};
  return res;
}

template<typename I> constexpr field_fl<I> make_field_fl(field_se<I> const fse){
  return make_field_fl<I>(fse.start,fse.end-1);
}

template<typename I> constexpr field_fl<I> make_field_fl(field_sl<I> const fsl){
  return make_field_fl<I>(fsl.start,fsl.start+fsl.length-1);
}

//-----

template<typename I> constexpr field_se<I> move_field(field_se<I> const fse, I const offset){
  return make_field_se<I>(fse.start+offset,fse.end+offset);
}

template<typename I> constexpr field_sl<I> move_field(field_sl<I> const fsl, I const offset){
  return make_field_sl<I>(fsl.start+offset,fsl.length);
}

template<typename I> constexpr field_fl<I> move_field(field_fl<I> const ffl, I const offset){
  return make_field_fl<I>(ffl.first+offset,ffl.last+offset);
}

//-----

template<typename I> constexpr I middle_field(field_fl<I> const ffl){
  return ffl.first + ((ffl.last-ffl.first)>>1);
}

template<typename I> constexpr I middle_field(field_se<I> const fse){
  return middle_field<I>(make_field_fl<I>(fse));
}

template<typename I> constexpr I middle_field(field_sl<I> const fsl){
  return middle_field<I>(make_field_fl<I>(fsl));
}

//-----

template<typename I> constexpr bool is_in_bounds(field_fl<I> ffl, field_fl<I> bounds){
  bool in_bounds = true;
  in_bounds &= (ffl.first >= bounds.first);
  in_bounds &= (ffl.last  <= bounds.last);
  return in_bounds;
}

template<typename I> constexpr bool is_in_bounds(field_se<I> fse, field_se<I> bounds){
  return is_in_bounds<I>(make_field_fl<I>(fse),make_field_fl<I>(bounds));
}

template<typename I> constexpr bool is_in_bounds(field_sl<I> fsl, field_sl<I> bounds){
  return is_in_bounds<I>(make_field_fl<I>(fsl),make_field_fl<I>(bounds));
}

//-----

} //namespace

#endif
