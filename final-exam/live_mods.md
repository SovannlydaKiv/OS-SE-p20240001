# Live Modification Tasks

## Part A Curveball
- **Instruction:** Edit `thread_demo.c` to spawn extra workers after originals joined; show LWP mapping changes.
- **Live Value:** 1 extra worker(s)
- **Commands run:** `gcc thread_demo.c -o thread_demo -pthread`
  `./thread_demo`

## Part D Curveball
- **Instruction:** Add a per-buyer purchase cap to `buy_widget` (reject if over cap); re-run `swarm`.
- **Live Value:** cap = 8
- **Commands run:** `cp ~/bin/buy_widget scripts/`
  `~/bin/buy_widget "GreedyBot" 10`
  `~/bin/swarm`

## Part E Curveball
- **Instruction:** Make `timed_job` idempotent using a marker token; trigger twice to prove skip.
- **Live Value:** token = IDEMPMARK
- **Commands run:** `cp ~/bin/timed_job scripts/`
  `~/bin/timed_job test_idempotent.log`
  `~/bin/timed_job test_idempotent.log`
  `cat test_idempotent.log`