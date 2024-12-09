//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 07 - Homework 05
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Employee {
public:
    std::string name;
    std::vector<std::shared_ptr<Employee>> subordinates;

    Employee(const std::string& name) : name(name) {}

    void addSubordinate(std::shared_ptr<Employee> subordinate) {
        subordinates.push_back(subordinate);
    }

    bool removeSubordinate(const std::string& name) {
        auto it = std::remove_if(subordinates.begin(), subordinates.end(),
            [&name](const std::shared_ptr<Employee>& emp) {
                return emp->name == name;
            });
        if (it != subordinates.end()) {
            subordinates.erase(it, subordinates.end());
            return true;
        }
        for (auto& emp : subordinates) {
            if (emp->removeSubordinate(name)) {
                return true;
            }
        }
        return false;
    }

    void displayHierarchy(int level = 0) const {
        for(int i = 0; i < level; ++i) std::cout << "  ";
        std::cout << name << std::endl;
        for(const auto& subordinate : subordinates) {
            subordinate->displayHierarchy(level + 1);
        }
    }
};

class OrganizationalChart {
public:
    std::shared_ptr<Employee> ceo;

    OrganizationalChart(const std::string& ceoName) {
        ceo = std::make_shared<Employee>(ceoName);
    }

    bool addEmployee(const std::string& managerName, const std::string& employeeName) {
        auto manager = findEmployee(ceo, managerName);
        if(manager) {
            manager->addSubordinate(std::make_shared<Employee>(employeeName));
            return true;
        }
        return false;
    }

    bool removeEmployee(const std::string& employeeName) {
        if(ceo->name == employeeName) return false;
        return ceo->removeSubordinate(employeeName);
    }

    void display() const {
        if(ceo) ceo->displayHierarchy();
    }

private:
    std::shared_ptr<Employee> findEmployee(std::shared_ptr<Employee> current, const std::string& name) {
        if(current->name == name) return current;
        for(auto& subordinate : current->subordinates) {
            auto found = findEmployee(subordinate, name);
            if(found) return found;
        }
        return nullptr;
    }
};

int main() {
    OrganizationalChart chart("CEO");
    chart.addEmployee("CEO", "Manager1");
    chart.addEmployee("CEO", "Manager2");
    chart.addEmployee("Manager1", "Employee1");
    chart.addEmployee("Manager1", "Employee2");
    chart.display();

    std::cout << "\nAfter removing Manager1:\n";
    chart.removeEmployee("Manager1");
    chart.display();

    return 0;
}