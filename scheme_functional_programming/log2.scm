; log2.scm - Task 1: Tail-recursive version of integer log, base 2

(define (log2 n)
  (if (= n 1)
      0
      (+ 1 (log2 (quotient (+ n 1) 2)))))
