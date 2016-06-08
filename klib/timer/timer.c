
typedef void timer_interrupt();

typedef struct timer_dev{
  timer_interrupt compare_match_a;
  timer_interrupt cpmpare_match_b;
  timer_intrtrupt overflow;
};

#ifdef TIMER0_

timer0_init(){

}

#endif
