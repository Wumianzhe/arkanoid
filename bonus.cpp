#include "bonus.hpp"
#include "racket.hpp"

using namespace Bonus;

void SpeedUp::hitBy(Racket* racket) { racket->collideWith(this); }
void SpeedDown::hitBy(Racket* racket) { racket->collideWith(this); }
void SizeUp::hitBy(Racket* racket) { racket->collideWith(this); }
void SizeDown::hitBy(Racket* racket) { racket->collideWith(this); }
void Shield::hitBy(Racket* racket) { racket->collideWith(this); }
void Randomizer::hitBy(Racket* racket) { racket->collideWith(this); }
void BallUp::hitBy(Racket* racket) { racket->collideWith(this); }
void Sticky::hitBy(Racket* racket) { racket->collideWith(this); }
