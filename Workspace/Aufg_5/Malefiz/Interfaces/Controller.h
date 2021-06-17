#pragma once


class Controller {
public:
    virtual void viewChanged() = 0;
    virtual ~Controller() = default;
};