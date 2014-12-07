(define (read-line)
  (let
    ((s ""))
    (do
      ((c (read-char)))
      ((or (eof-object? c) (char=? #\newline c)))
      (begin
        (set! s (string-append s (string c)))
        (set! c (read-char))))
    s))

(define (read-number)
  (let
    ((line (read-line)))
    (if (string-null? line)
      0
      (string->number line))))

(define (vector->message vec)
  (apply
    string-append
    (map
      (lambda (l)
        (list->string (reverse l)))
      (vector->list vec))))

(define (get-column i n)
  (let*
    ((column-end (ceiling (/ (+ i 1) n)))
     (even-row (= 0 (modulo column-end 2))))
    (if even-row
      (- n 1 (modulo i n))
      (modulo i n))))

(define (toandfro n crypted-message)
  (let
    ((decoded-message (make-vector n '()))
     (i 0))
    (for-each
      (lambda (c)
        (let*
          ((column-idx (get-column i n))
           (column (vector-ref decoded-message column-idx)))
          (vector-set! decoded-message column-idx (cons c column))
          (set! i (+ i 1))))
      (string->list crypted-message))
    (vector->message decoded-message)))

(do 
  ((n (read-number)))
  ((= n 0))
  (format (current-output-port) "~A\n" (toandfro n (read-line)))
  (set! n (read-number)))
