/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"

#include "Core/Gs2Core.h"
#include "Schedule/Request/TriggerByStampSheetRequest.h"
#include "Schedule/Result/TriggerByStampSheetResult.h"

namespace Gs2::Schedule::Task::Rest
{
    class GS2SCHEDULE_API FTriggerByStampSheetTask final : public Gs2::Core::Util::TGs2Future<Result::FTriggerByStampSheetResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FTriggerByStampSheetRequestPtr Request;
    public:
        explicit FTriggerByStampSheetTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FTriggerByStampSheetRequestPtr Request
        );
        FTriggerByStampSheetTask(
            const FTriggerByStampSheetTask& From
        );
        virtual ~FTriggerByStampSheetTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FTriggerByStampSheetResultPtr> Result) override;
    };
    typedef TSharedPtr<FTriggerByStampSheetTask, ESPMode::ThreadSafe> FTriggerByStampSheetTaskPtr;
}