{Push  -24			   
}{Label
  11:loop	 		
}Read-10-chars({Push  1 	
}{Push  10 	 	 
}{Call
 	3:read(1,10) 		
})Read-WS({Push  0  
}{ReadChar	
	 })Read-5-chars({Push  11 	 		
}{Push  5 	 	
}{Call
 	3:read(11,5) 		
}){Call
 	8:lookSubstr	   
}{Push  20 		   
}{ReadChar	
	 }{Push  1 	
}{Add	   }{Dup 
 }{JumpIfNeg
		11:loop	 		
}{End


}{Label
  **********FUNCTION:8:lookSubstr**********	   
}{Push  1 	
}{Label
  9:loop	  	
}{Dup 
 }{Push  7 			
}{Sub	  	}{JumpIfZero
	 10:notfound	 	 
}{Dup 
 }{Call
 	4:startswith	  
}{Swap 
	}{Push  1 	
}{Add	   }{Swap 
	}{JumpIfZero
	 9:loop	  	
}{Pop 

}{Push  1 	
}{PrintNum	
 	}{Push  10 	 	 
}{PrintChar	
  }{Return
	
}{Label
  10:notfound	 	 
}{Pop 

}{Push  0  
}{PrintNum	
 	}{Push  10 	 	 
}{PrintChar	
  }{Return
	
}**********END-OF-8:lookSubstr**********{Label
  **********FUNCTON:3:read*********** 		
}{Dup 
 }{Push  0  
}{Swap 
	}{Store		 }{Add	   }Loop10({Label
  2:loop 	 
}{Dup 
 }{push  0  
}{Retrieve			}{Sub	  	}{ReadChar	
	 }{Call
 	1:dec(mem=0)  	
}{Push  0  
}{Retrieve			}{Push  -1		
}{Mult	  
}{JumpIfNeg
		2:loop 	 
}{Pop 

}{Return
	
})********END-OF-3:read*********{Label
  ********FUNCTION:1:dec*********(mem=0)  	
}{Push  0  
}{Retrieve			}{Push  1 	
}{Sub	  	}{Push  0  
}{Swap 
	}{Store		 }{Return
	
}*****END-OF-1:dec********{Label
  **********FUNCTION:4:startswith***********	  
}{Push  0  
}{Push  5 	 	
}{Store		 }{Label
  5:loop	 	
}GetLeftSide({Dup 
 }{Push  1 	
}{Add	   }{Swap 
	}{Retrieve			}){Push  5 	 	
}GetCounter({Push  0  
}{Retrieve			)5-Minus-Counter({Sub	  	})GetRightSide({Push  11 	 		
}{Add	   }{Retrieve			})Compare({Sub	  	}){Call
 	1:dec(mem=0)  	
}{Push  0  
}{Retrieve			}{JumpIfZero
	 6:EOS		 
}{JumpIfZero
	 5:loop	 	
}EscapedBeforeEOS{Push  0  
}{Swap 
	}{Pop 

}{Return
	
}{Label
  6:EOS		 
}{JumpIfZero
	 7:zeroTo1			
}{Push  0  
}{Swap 
	}{Pop 

}{Return
	
}{Label
  7:zeroTo1			
}{Push  1 	
}{Swap 
	}{Pop 

}{Return
	
}***********END-OF-4:startswith**************