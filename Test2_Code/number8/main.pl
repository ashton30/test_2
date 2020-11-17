#define several global variables
$a = 15;
$x = 1;
$y = 3;
$z = 5;

#this function is being used as the control group.
#it simply prints the variables.
sub sub1{
    print $a." sub 1\n";
    print $y." sub 1\n";
    print $z." sub 1\n";
    print $x." sub 1\n";
    
}
#this function defines static scoped local variables
#it prints the variables and then calls sub4 to show 
#that nested values remain the same. It then returns sub1 to see 
#what variables get passed if any.
sub sub2{
    my $a = 50;
    my $y = 55;
    my $z = 60;
    my $x = 65;
    print $a." sub 2\n";
    print $y." sub 2\n";
    print $z." sub 2\n";
    print $x." sub 2\n";
    sub4();
    sub sub4{
        print $a." sub 1\n";
        print $y." sub 1\n";
        print $z." sub 1\n";
        print $x." sub 1\n";
    }
    return sub1();
}
#this function defines dynamic scoped local variables
#it prints the variables and then returns sub1 to see 
#what variables get passed.
sub sub3{
    local $a = 21;
    local $y = 22;
    local $z = 23;
    local $x = 25;
    print $a." sub 3\n";
    print $y." sub 3\n";
    print $z." sub 3\n";
    print $x." sub 3\n";
    return sub1();
}
#the idea is to call the first function to see the global variables print
print "first call\n";
sub1();
print "**************************\n";
#then i call sub2 which has locally defined static scope variables.
print "second call\n";
sub2();
print "**************************\n";
#then i call sub3 which has locally defined dynamic variables
print "third call\n";
sub3();
