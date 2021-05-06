#define dVALUES 256
#define mSIZE(_x,_t) (sizeof(_x)/sizeof(_t))

const uint8_t gapseq[] = {132,57,23,10,4,1,0}; //Shell-Sort: optimal Gap-Sequence for 256 Values


/**
 *
 */
void sorting::shellsort::fillran(uint16_t* data, uint16_t len){
  /* initialize random seed: */
  srand ( time(NULL) );
  for(uint16_t ii=0; ii<len; ++ii){
      data[ii]  = rand() % 256;
  }
  return;
}

/**
 *
 */
string sorting::shellsort::List(uint16_t const * const data, uint16_t len){
  stringstream ss;
  for(uint16_t ii=0; ii<len; ++ii){
    ss << data[ii] << " ";
  }
  return ss.str();
}

/**
 *
 */
uint16_t sorting::shellsort::Initgap(uint16_t len){
    uint16_t ii;
    for(ii=0;len-1;++ii){
        if(gapseq[ii]<len){
            break;
        }
    }
    return ii;
}

/**
 *
 */
void sorting::shellsort::Sort(uint16_t* data, uint16_t len, uint16_t init){
  uint16_t inc = gapseq[init];
  uint16_t ii;
  uint16_t ij;
  uint16_t tmp;

  while(inc > 0){
    for(ii=inc;ii<len;++ii){
      tmp=data[ii];
      ij=ii;
      while((ij>=inc) && (data[ij-inc]>tmp)){
          data[ij] = data[ij-inc];
          ij-=inc;
      }
      data[ij] = tmp;
    }
    inc = gapseq[++init];
  }
  return;
}
