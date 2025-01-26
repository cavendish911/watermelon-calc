#include <httplib.h>
#include <string>
#include <cstdlib>

int main() {
    httplib::Server svr;

    svr.Get("/calculate", [](const httplib::Request &req, httplib::Response &res) {
        double num1 = std::stod(req.get_param_value("num1"));
        double num2 = std::stod(req.get_param_value("num2"));
        std::string op = req.get_param_value("op");
        double result = 0;

        if (op == "+") result = num1 + num2;
        else if (op == "-") result = num1 - num2;
        else if (op == "*") result = num1 * num2;
        else if (op == "/" && num2 != 0) result = num1 / num2;
        else {
            res.set_content("Invalid operation", "text/plain");
            return;
        }

        res.set_content(std::to_string(result), "text/plain");
    });

    std::cout << "Server running at http://localhost:8080\n";
    svr.listen("localhost", 8080);
}
