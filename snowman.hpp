//
// Created by Yuri Grigorian on 10/03/2021.
//



#ifndef SNOWMAN_A_SNOWMAN_HPP
#define SNOWMAN_A_SNOWMAN_HPP

#include <iostream>
#include <vector>

#define BASE_TEN 10
#define IDX_BASE 0
#define IDX_TORSO 1
#define IDX_R_ARM 2
#define IDX_L_ARM 3
#define IDX_R_EYE 4
#define IDX_L_EYE 5
#define IDX_NOSE 6
#define IDX_HAT 7

namespace ariel {
    std::string snowman(const unsigned int conf);

    class ValidationError : public std::runtime_error {
        public:
            ValidationError(const char *txt);
    };

    class BaseValidator {
        public:
            virtual void validate(unsigned int target) = 0;
    };

    /*
     * A simple input validator to validate the validity of the config.
     */
    class InputValidator : BaseValidator {
            const static unsigned int MIN_DIGIT = 1;
            const static unsigned int MAX_DIGIT = 4;
            const static unsigned int MIN_NUM = 11111111;
            const static unsigned int MAX_NUM = MIN_NUM * MAX_DIGIT;


        public:
            void validate(const unsigned int target) override;
    };


    class Toolz {
        public:
            /*
             * Extract the nth element from a number. Will not validate number correctness. Index is array like.
             */
            static unsigned int extract_n_digit_from_right(const unsigned int target, const unsigned idx);
    };

    // Holds visual object that span across two lines
    struct UpperLowerObject {
        std::string upper;
        std::string lower;

        UpperLowerObject(std::string &&u, std::string &&l) : upper(u), lower(l) {};
    };

    // Holds Single line objects
    struct SingleObject {
        std::string item;

        SingleObject(std::string &&i) : item(i) {};
    };

    /*
     * A data holding class for painting data.
     */
    class DB {
        public:
            static const std::vector <UpperLowerObject> hats;

            static const std::vector <UpperLowerObject> right_hands;

            static const std::vector <UpperLowerObject> left_hands;

            static const std::vector <SingleObject> noses;

            static const std::vector <SingleObject> eyes;

            static const std::vector <SingleObject> torsos;

            static const std::vector <SingleObject> bases;

    };

    std::string create_snowman(const UpperLowerObject &hat,
                               const UpperLowerObject &right_hand,
                               const UpperLowerObject &left_hand,
                               const SingleObject &nose,
                               const SingleObject &right_eye,
                               const SingleObject &left_eye,
                               const SingleObject &torso,
                               const SingleObject &base);


}

#endif //SNOWMAN_A_SNOWMAN_HPP
