#include "medico.h"


Doctor::Doctor(std::string name = ""):m_name(name){}
std::ostream& operator<<(std::ostream &out, const Doctor &doc)
{
    unsigned int length = doc.m_patient.size();
    out << doc.m_name << "[ ";
    for (unsigned int count = 0; count < length; ++count)
            out << doc.m_patient[count]->getName() << ' ';
    out << "]";
    return out;
}

void Doctor::addPatient(Patient *pat){
    for(size_t i = 0; i < m_patient.size(); i++){
        if(m_patient[i]->getName() == pat->getName())
            throw "Medico já possui este paciente";
        
    }
	//verifica se nao possui esse pat
	// Our doctor will add this patient
	m_patient.push_back(pat);
	// and the patient will also add this doctor
	pat->addDoctor(this);
}

void Doctor::rmPatient(std::string patId){
	for(size_t i = 0; i < m_patient.size(); i++){
	    if(m_patient[i]->getName() == patId){
			m_patient[i]->rmDoctor(getName());
			m_patient.erase(m_patient.begin() + i);
            return;
		}
	}
}
 
std::string Doctor::getName(){
    return m_name;
}