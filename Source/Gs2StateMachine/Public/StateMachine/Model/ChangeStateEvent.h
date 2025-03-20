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
    class GS2STATEMACHINE_API FChangeStateEvent final : public FGs2Object, public TSharedFromThis<FChangeStateEvent>
    {
        TOptional<FString> TaskNameValue;
        TOptional<FString> HashValue;
        TOptional<int64> TimestampValue;

    public:
        FChangeStateEvent();
        FChangeStateEvent(
            const FChangeStateEvent& From
        );
        virtual ~FChangeStateEvent() override = default;

        TSharedPtr<FChangeStateEvent> WithTaskName(const TOptional<FString> TaskName);
        TSharedPtr<FChangeStateEvent> WithHash(const TOptional<FString> Hash);
        TSharedPtr<FChangeStateEvent> WithTimestamp(const TOptional<int64> Timestamp);

        TOptional<FString> GetTaskName() const;
        TOptional<FString> GetHash() const;
        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;


        static TSharedPtr<FChangeStateEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FChangeStateEvent, ESPMode::ThreadSafe> FChangeStateEventPtr;
}