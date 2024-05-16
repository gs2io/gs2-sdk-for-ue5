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

#include "StateMachine/Model/Event.h"

namespace Gs2::StateMachine::Model
{
    FEvent::FEvent():
        EventTypeValue(TOptional<FString>()),
        ChangeStateEventValue(nullptr),
        EmitEventValue(nullptr)
    {
    }

    FEvent::FEvent(
        const FEvent& From
    ):
        EventTypeValue(From.EventTypeValue),
        ChangeStateEventValue(From.ChangeStateEventValue),
        EmitEventValue(From.EmitEventValue)
    {
    }

    TSharedPtr<FEvent> FEvent::WithEventType(
        const TOptional<FString> EventType
    )
    {
        this->EventTypeValue = EventType;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithChangeStateEvent(
        const TSharedPtr<FChangeStateEvent> ChangeStateEvent
    )
    {
        this->ChangeStateEventValue = ChangeStateEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithEmitEvent(
        const TSharedPtr<FEmitEvent> EmitEvent
    )
    {
        this->EmitEventValue = EmitEvent;
        return SharedThis(this);
    }
    TOptional<FString> FEvent::GetEventType() const
    {
        return EventTypeValue;
    }
    TSharedPtr<FChangeStateEvent> FEvent::GetChangeStateEvent() const
    {
        return ChangeStateEventValue;
    }
    TSharedPtr<FEmitEvent> FEvent::GetEmitEvent() const
    {
        return EmitEventValue;
    }

    TSharedPtr<FEvent> FEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEvent>()
            ->WithEventType(Data->HasField(ANSI_TO_TCHAR("eventType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithChangeStateEvent(Data->HasField(ANSI_TO_TCHAR("changeStateEvent")) ? [Data]() -> Model::FChangeStateEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeStateEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FChangeStateEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeStateEvent")));
                 }() : nullptr)
            ->WithEmitEvent(Data->HasField(ANSI_TO_TCHAR("emitEvent")) ? [Data]() -> Model::FEmitEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("emitEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FEmitEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("emitEvent")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EventTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("eventType", EventTypeValue.GetValue());
        }
        if (ChangeStateEventValue != nullptr && ChangeStateEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeStateEvent", ChangeStateEventValue->ToJson());
        }
        if (EmitEventValue != nullptr && EmitEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("emitEvent", EmitEventValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FEvent::TypeName = "Event";
}