#include<iostream>
#include "ssh_connection.h"
#include "menu.h"
int main() {
	int option;
	std::string ip, user, ppwd;
	ssh_session session = nullptr;
	bool logra_ingresar = false;
	try {
		do {
			menu();
			if (!(std::cin >> option)) {
				throw std::runtime_error("Acabas de ingresar una entrada que no es valida");
			}
			switch (option) {
			case 1:
				std::cout << "Enter the ip:" << std::endl;
				std::cin >> ip;
				std::cout << "Enter the username:" << std::endl;
				std::cin >> user;
				std::cout << "Enter the password:" << std::endl;
				std::cin >> ppwd;
				 session = connection(ip, user, ppwd);
				if (session == nullptr) {
					std::cerr << "Error al conectar\n";
				}
				else {
					std::cout << "La conexion fue exitosa\n";
					std::string comando;
					std::cin.ignore();
					std::cout << "Ingresa el comando que deseas ejecutar:";
					std::getline(std::cin,comando);
					std::string resultado = command_execution(session,comando);
					std::cout << "Resultado del comando:\n" << resultado << "\n";
					
				}
				break;
			case 2:
				std::cout << "Ingresa la direcion ip que desea verificar:\n";
				std::cin >> ip;
				if (verificar(ip)) {
					std::cout << "El puerto ssh esta abierto para la direccion" << ip << "\n";
				}
				else {
					std::cout << "No es posible acceder al ssh debido a que no esta activado\n";
				}
				break;
				case 3:
					std::cout << "Saliendo del sistema ......";
					if (session != nullptr) {
						ssh_disconnect(session);
						ssh_free(session);
					}
					break;
			default:
				std::cout << "Opcion no valida, intentelo de nuevo";
				break;
			}
		} while (option != 3);
	}
	catch (const std::exception& e) {
		std::cerr << "Error:" << e.what() << "\n";
	}
	return 0;
}