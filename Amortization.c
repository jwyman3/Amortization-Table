#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define loanMin 5000
#define loanMax 2000000
#define aprMin 1.0
#define aprMax 25.0
#define yearMin 3
#define yearMax 40

double getLoanTerm();
double getLoanAmount();
double getInterest();

double calcPrincipal();
double calcInterest();
double calcBalance();
double printTable();
double calcPayment();


int main(){
    double months = 0;
    double years = 0;
    double loan = 0;
    double apr = 0;
    double payment = 0;

    getLoanTerm(&months, &years);
    if(months == 0){
        return 0;
    }
    getInterest(&apr);
    getLoanAmount(&loan);
    calcPayment(months, apr, loan, &payment);
    printTable(months, years, apr, loan, payment);

    return 0;
}

double printTable(int months, int years, double apr, double loan, double payment){
    int i;
    int currentMonth[months + 1];
    double interestAmor[months + 1];
    double principalAmor[months + 1];
    double balanceAmor[months + 2];
    
    int *pointCurrentMonth = currentMonth;
    double *pointInterestAmor = interestAmor;
    double *pointPrincipalAmor = principalAmor;
    double *pointBalanceAmor = balanceAmor;
    double totalInterest, totalCost;
    double paidPrincipal = 0;

    for(i = 1; i  != months + 1; i++){
        *pointCurrentMonth = i;

        calcBalance(loan, currentMonth, paidPrincipal, &*pointBalanceAmor);
        calcInterest(apr, *pointBalanceAmor, &*pointInterestAmor);
        calcPrincipal(payment, *pointInterestAmor,&*pointPrincipalAmor);
        paidPrincipal = paidPrincipal + *pointPrincipalAmor;
        
        *pointPrincipalAmor++;
        *pointBalanceAmor++;
        *pointInterestAmor++;
        *pointCurrentMonth++;
        
    }
    totalCost = payment * months;
    totalInterest = totalCost - loan;
    
    printf("\n|Month|Interest|Principal|Balance   |\n");
    printf("|-----|--------|---------|----------|\n");
    for ( i = 0; i != months; i++){
    printf("|%5d|%8.2lf|%9.2lf|%10.2lf|\n",currentMonth[i], interestAmor[i], principalAmor[i], balanceAmor[i+1]);
    }
    printf("Monthly payment: %0.2lf \n", payment);
    printf("Total cost of the loan: $%0.2lf \n", totalCost);
    printf("Total interest paid: $%0.2lf \n", totalInterest);
    printf("Total principal: %0.2lf \n", loan);
}

double calcInterest(double apr, double currentBalance, double* pointInterest){
    double currentInterest;
    //current period Interest = balance * apr / 12
    currentInterest = currentBalance * (apr/12);
    *pointInterest = currentInterest;
}

double calcPrincipal(double payment, double currentInterest, double* pointPrincipal){
    double currentPrincipal = 0;
 //   principal paid == payment - interest
    currentPrincipal = payment - currentInterest;
    *pointPrincipal = currentPrincipal;
}

double calcBalance(double loan, int currentMonth, double paidPrincipal, double* pointBalance){
  // initially, balance == loan, then after month 0, balance == loan - principal paid
double currentBalance;

  if(currentMonth == 0){
      currentBalance = loan;
  }
  if(currentMonth != 0){
      currentBalance = loan - paidPrincipal;
  }
    *pointBalance = currentBalance;
}

double calcPayment(double months, double apr, double loan, double* pointPayment){
    double payment;
    double pR = apr / 12;
    double pRPlus;
    double pwPRPlus;
    double pwPRPlusMinus;

    pRPlus = pR + 1;
    pwPRPlus = pow(pRPlus, months);
    pwPRPlusMinus = pwPRPlus - 1;

    payment = (loan * (pR * pwPRPlus / pwPRPlusMinus));
    *pointPayment = payment;

}

double getLoanTerm(double* pointMonths, double* pointYears){
    double years;
    do{
        printf("Enter the length of the loan (in years, between %d and %d) or enter 0 to quit: ", yearMin, yearMax);
        scanf("%lf", &years);
        if(years == 0){
            break;
        }else
        if( years < yearMin || years > yearMax){
            printf("That is an invalid entry. Please try again.\n");
        }
    }while(years < yearMin || years > yearMax);
    *pointMonths = years * 12;
    *pointYears = years;
}


double getInterest(double* pointApr){
    double apr;

    do{
        printf("\nEnter the interest rate of the loan (%0.2f%% to %0.2f%%): ", aprMin, aprMax);
        scanf("%lf", &apr);
        if(apr < aprMin || apr > aprMax){
            printf("That is an invalid entry. Please try again.\n");
        }
    }while(apr < aprMin || apr > aprMax);
    *pointApr = apr / 100;
}

double getLoanAmount(double* pointLoan){
    double loan;

    do{
        printf("\nEnter the mortgage amount ($%d to $%d): ", loanMin, loanMax);
        scanf("%lf", &loan);
        if(loan < loanMin || loan > loanMax){
            printf("That is an invalid entry. Please try again.\n");
        }
    }while(loan < loanMin || loan > loanMax);
    *pointLoan = loan;
}
