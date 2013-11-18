BEGIN {	
	sumError = 0;
	sumErrorSq = 0;
	nonZeroCount = 0;
	nanCount = 0;
	zeroCount = 0;
}

{
	if($1 != 0) 	#successfull prediction
	{
		print 0;
		sumError += 0;
		zeroCount ++;
	}
	else if($2 == 0)
	{
		print "NaN";
		#sumError += 0;
		nanCount ++;
	}
	else
	{
		error = sqrt(($10-$7)^2 + ($9-$6)^2);
		sumError += error;
		sumErrorSq += error^2;
		nonZeroCount ++;
		print error;
	}	
} 

END { 
	print "#zeroes = " zeroCount;
	print "#nonZeroes= " nonZeroCount;
	print "#nan= " nanCount;
	print "#Sum= " sumError;
	print "#avgError = " sumError/(zeroCount+nonZeroCount);
	print "#stdDev= " sqrt(sumErrorSq/(zeroCount + nonZeroCount) - (sumError/(zeroCount+nonZeroCount))^2);

}

