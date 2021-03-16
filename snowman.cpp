#include "snowman.hpp"
#include <iostream>
#include <stdexcept>
#include <math.h>

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

namespace ariel {
    /*
     * Custom validation error exception.
     */

    ValidationError::ValidationError(const char *txt) : std::runtime_error(txt) {};

    /*
     * A simple input validator to validate the validity of the config.
     */
    void InputValidator::validate(const unsigned int target) {

        // Is within boundaries?
        if (target < MIN_NUM || target > MAX_NUM) {
            throw ValidationError("Invalid number size.");
        }

        // Is all digits ok?
        unsigned int tmp = target;
        while (tmp != 0) {
            if (tmp % BASE_TEN > MAX_DIGIT || tmp % BASE_TEN < MIN_DIGIT) {
                throw ValidationError("Invalid choice for one of the objects.");
            }
            tmp = tmp / BASE_TEN;
        }
    }

    /*
     * A generic class for utility functions.
     */
    unsigned int Toolz::extract_n_digit_from_right(const unsigned int target, const unsigned idx) {
        return (int) (target / pow(BASE_TEN, idx)) % BASE_TEN;
    }

    /*
     * Static init DB
     */

    const std::vector <UpperLowerObject> DB::hats{{"     ",
                                                          "_===_"},
                                                  {" ___ ",
                                                          "....."},
                                                  {"  _  ",
                                                          " /_\\ "},
                                                  {" ___ ",
                                                          "(_*_)"}};


    const std::vector <UpperLowerObject> DB::right_hands{{" ",
                                                                 ">"},
                                                         {"/",
                                                                 " "},
                                                         {" ",
                                                                 "\\"},
                                                         {" ",
                                                                 " "}};

    const std::vector <UpperLowerObject> DB::left_hands{{" ",
                                                                "<"},
                                                        {"\\",
                                                                " "},
                                                        {" ",
                                                                "/"},
                                                        {" ",
                                                                " "}};


    const std::vector <SingleObject> DB::noses{{","},
                                               {"."},
                                               {"_"},
                                               {" "}};

    const std::vector <SingleObject> DB::eyes{{"."},
                                              {"o"},
                                              {"O"},
                                              {"-"}};

    const std::vector <SingleObject> DB::torsos{{" : "},
                                                {"] ["},
                                                {"> <"},
                                                {"   "}};;

    const std::vector <SingleObject> DB::bases{{" : "},
                                               {"\" \""},
                                               {"___"},
                                               {"   "}};

    std::string create_snowman(const UpperLowerObject &hat,
                               const UpperLowerObject &right_hand,
                               const UpperLowerObject &left_hand,
                               const SingleObject &nose,
                               const SingleObject &right_eye,
                               const SingleObject &left_eye,
                               const SingleObject &torso,
                               const SingleObject &base) {

        std::stringstream fmt;

        fmt << " " << hat.upper << "\n"
            << " " << hat.lower << "\n"
            << left_hand.upper << "(" << left_eye.item << nose.item << right_eye.item << ")" << right_hand.upper << "\n"
            << left_hand.lower << "(" << torso.item << ")" << right_hand.lower << "\n"
            << " " << "(" << base.item << ")" << " ";

        return fmt.str();
    }

    std::string snowman(const unsigned int conf) {
        // Ideally to be used with a pipeline of validators using a validation manager.
        InputValidator v{};

        try {
            v.validate(conf);
            return create_snowman(DB::hats.at(Toolz::extract_n_digit_from_right(conf, IDX_HAT) - 1),
                                  DB::right_hands.at(Toolz::extract_n_digit_from_right(conf, IDX_R_ARM) - 1),
                                  DB::left_hands.at(Toolz::extract_n_digit_from_right(conf, IDX_L_ARM) - 1),
                                  DB::noses.at(Toolz::extract_n_digit_from_right(conf, IDX_NOSE) - 1),
                                  DB::eyes.at(Toolz::extract_n_digit_from_right(conf, IDX_R_EYE) - 1),
                                  DB::eyes.at(Toolz::extract_n_digit_from_right(conf, IDX_L_EYE) - 1),
                                  DB::torsos.at(Toolz::extract_n_digit_from_right(conf, IDX_TORSO) - 1),
                                  DB::bases.at(Toolz::extract_n_digit_from_right(conf, IDX_BASE) - 1));

        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            throw;
        }

    }

}