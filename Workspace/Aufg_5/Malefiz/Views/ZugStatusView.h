#pragma once

class ZugStatusView;

#include <memory>

#include "..\Interfaces\View.h"
#include "..\Models\ZugStatus.h"


class ZugStatusView : public View {
private:
    std::shared_ptr<ZugStatus> status;
public:
    explicit ZugStatusView(std::shared_ptr<ZugStatus>);
    void modelChanged();
    void show();
};