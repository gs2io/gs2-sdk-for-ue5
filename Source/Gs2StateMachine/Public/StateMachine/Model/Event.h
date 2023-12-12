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
#include "ChangeStateEvent.h"
#include "EmitEvent.h"

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FEvent final : public Gs2Object, public TSharedFromThis<FEvent>
    {
        TOptional<FString> EventTypeValue;
        TSharedPtr<FChangeStateEvent> ChangeStateEventValue;
        TSharedPtr<FEmitEvent> EmitEventValue;

    public:
        FEvent();
        FEvent(
            const FEvent& From
        );
        virtual ~FEvent() override = default;

        TSharedPtr<FEvent> WithEventType(const TOptional<FString> EventType);
        TSharedPtr<FEvent> WithChangeStateEvent(const TSharedPtr<FChangeStateEvent> ChangeStateEvent);
        TSharedPtr<FEvent> WithEmitEvent(const TSharedPtr<FEmitEvent> EmitEvent);

        TOptional<FString> GetEventType() const;
        TSharedPtr<FChangeStateEvent> GetChangeStateEvent() const;
        TSharedPtr<FEmitEvent> GetEmitEvent() const;


        static TSharedPtr<FEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEvent, ESPMode::ThreadSafe> FEventPtr;
}