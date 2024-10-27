import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Header from "./components/Header";
import Home from "./components/Home";
import Appointments from "./components/Appointments";
import Patients from "./components/Patients";
import Doctors from "./components/Doctors";
import DoctorProfile from "./components/DoctorProfile";
import Admin from "./components/Admin";
import Footer from "./components/Footer";
import NotFound from "./components/NotFound";
import ScrollToTopButton from "./components/ScrollToTopButton";
import ScrollToTop from "./components/ScrollToTop";
import AboutUs from "./pages/AboutUs";
import Services from "./pages/Services";
import PrivacyPolicy from "./pages/PrivacyPolicy";
import TermsOfService from "./pages/TermsOfService";
import ContactUs from "./pages/ContactUs";
import SignUp from "./components/SignUp";
import Login from "./components/Login";
import { useState } from "react";
import LoginContext from "./context/LoginContext";

function App() {
  const [doctors, setDoctors] = useState([
    {
      id: 1,
      name: "Dr. Aarav Sharma",
      specialty: "Cardiology",
      patients: 120,
      appointments: 450,
      experience: 15,
      qualifications: "MD, FACC",
      bio: "Dr. Aarav Sharma is a renowned cardiologist with over 15 years of experience in treating complex heart conditions.",
    },
    {
      id: 2,
      name: "Dr. Priya Gupta",
      specialty: "Pediatrics",
      patients: 200,
      appointments: 600,
      experience: 10,
      qualifications: "MD, FAAP",
      bio: "Dr. Priya Gupta is a compassionate pediatrician dedicated to providing comprehensive care for children of all ages.",
    },
    {
      id: 3,
      name: "Dr. Rohan Verma",
      specialty: "Orthopedics",
      patients: 150,
      appointments: 500,
      experience: 12,
      qualifications: "MD, FAAOS",
      bio: "Dr. Rohan Verma specializes in sports medicine and joint replacement surgeries, helping patients regain mobility and improve their quality of life.",
    },
    {
      id: 4,
      name: "Dr. Ananya Rao",
      specialty: "Neurology",
      patients: 100,
      appointments: 350,
      experience: 18,
      qualifications: "MD, PhD",
      bio: "Dr. Ananya Rao is a leading neurologist with expertise in treating a wide range of neurological disorders and conducting groundbreaking research.",
    },
    {
      id: 5,
      name: "Dr. Sameer Joshi",
      specialty: "Dermatology",
      patients: 180,
      appointments: 550,
      experience: 8,
      qualifications: "MD, FAAD",
      bio: "Dr. Sameer Joshi is a skilled dermatologist specializing in both medical and cosmetic dermatology, helping patients achieve healthy and beautiful skin.",
    },
    {
      id: 6,
      name: "Dr. Nisha Mehta",
      specialty: "Gynecology",
      patients: 350,
      appointments: 650,
      experience: 10,
      qualifications: "MD, PhD",
      bio: "Dr. Nisha Mehta is an experienced gynecologist providing comprehensive women's health care, specializing in reproductive health, pregnancy care, and preventive medicine for women of all ages.",
    },
    {
      id: 7,
      name: "Dr. Karan Singh",
      specialty: "General Practitioner",
      patients: 250,
      appointments: 620,
      experience: 12,
      qualifications: "MD, PhD",
      bio: "Dr. Karan Singh is an experienced general practitioner providing comprehensive primary care and preventive medicine for patients of all ages.",
    },
    {
      id: 8,
      name: "Dr. Deepak Patel",
      specialty: "Anesthesiology",
      patients: 350,
      appointments: 750,
      experience: 17,
      qualifications: "MD, PhD",
      bio: "Dr. Deepak Patel is an experienced anesthesiologist committed to ensuring patient comfort and safety during surgical procedures.",
    },
    {
      id: 9,
      name: "Dr. Ravi Choudhary",
      specialty: "Ophthalmology",
      patients: 150,
      appointments: 450,
      experience: 15,
      qualifications: "MD, PhD",
      bio: "Dr. Ravi Choudhary is an experienced ophthalmologist specializing in eye surgeries and vision care, helping patients maintain their sight.",
    },
  ]);
  

  const [isLoggedIn, setIsLoggedIn] = useState(false);

  return (
    <LoginContext.Provider value={{ isLoggedIn, setIsLoggedIn }}>
      <Router>
        <ScrollToTop />
        <div className="bg-light min-h-screen font-sans text-primary">
          <Header />
          <main className="container mx-auto px-4 py-8">
            <Routes>
              <Route path="/" element={<Home />} />
              <Route path="/appointments" element={<Appointments />} />
              <Route path="/patients" element={<Patients />} />
              <Route path="/doctors" element={<Doctors doctors={doctors} />} />
              <Route
                path="/doctor/:id"
                element={<DoctorProfile doctors={doctors} />}
              />
              <Route path="/admin" element={<Admin />} />
              <Route path="/about-us" element={<AboutUs />} />
              <Route path="/services" element={<Services />} />
              <Route path="/privacy-policy" element={<PrivacyPolicy />} />
              <Route path="/terms-of-service" element={<TermsOfService />} />
              <Route path="/contact-us" element={<ContactUs />} />
              <Route path="/signup" element={<SignUp />} />
              <Route path="/login" element={<Login />} />
              <Route path="*" element={<NotFound />} />
            </Routes>
          </main>
          <ScrollToTopButton />
          <Footer />
        </div>
      </Router>
    </LoginContext.Provider>
  );
}

export default App;
