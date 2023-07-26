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
#include "../Model/Status.h"

namespace Gs2::StateMachine::Result
{
    class GS2STATEMACHINE_API FExitStateMachineResult final : public TSharedFromThis<FExitStateMachineResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        
    public:
        
        FExitStateMachineResult();
        FExitStateMachineResult(
            const FExitStateMachineResult& From
        );
        ~FExitStateMachineResult() = default;

        TSharedPtr<FExitStateMachineResult> WithItem(const TSharedPtr<Model::FStatus> Item);

        TSharedPtr<Model::FStatus> GetItem() const;

        static TSharedPtr<FExitStateMachineResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExitStateMachineResult, ESPMode::ThreadSafe> FExitStateMachineResultPtr;
}