from utils.ploting import plot_function
from functions.drop_wave import drop_wave, DOMAIN_DW
from functions.eggholder import eggholder, DOMAIN_EG

if __name__=='__main__':
    plot_function(drop_wave, DOMAIN_DW, DOMAIN_DW, "Drop wave function")
    plot_function(eggholder, DOMAIN_EG, DOMAIN_EG, "Eggholder function")