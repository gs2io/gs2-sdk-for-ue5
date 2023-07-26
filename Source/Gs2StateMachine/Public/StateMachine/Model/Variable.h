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
#include "Core/Gs2Object.h"

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FVariable final : public Gs2Object, public TSharedFromThis<FVariable>
    {
        TOptional<FString> StateMachineNameValue;
        TOptional<FString> ValueValue;

    public:
        FVariable();
        FVariable(
            const FVariable& From
        );
        virtual ~FVariable() override = default;

        TSharedPtr<FVariable> WithStateMachineName(const TOptional<FString> StateMachineName);
        TSharedPtr<FVariable> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetStateMachineName() const;
        TOptional<FString> GetValue() const;


        static TSharedPtr<FVariable> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVariable, ESPMode::ThreadSafe> FVariablePtr;
}