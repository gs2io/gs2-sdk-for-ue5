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

#include "Deploy/Model/Event.h"

namespace Gs2::Deploy::Model
{
    FEvent::FEvent():
        EventIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        ResourceNameValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        MessageValue(TOptional<FString>()),
        EventAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FEvent::FEvent(
        const FEvent& From
    ):
        EventIdValue(From.EventIdValue),
        NameValue(From.NameValue),
        ResourceNameValue(From.ResourceNameValue),
        TypeValue(From.TypeValue),
        MessageValue(From.MessageValue),
        EventAtValue(From.EventAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FEvent> FEvent::WithEventId(
        const TOptional<FString> EventId
    )
    {
        this->EventIdValue = EventId;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithMessage(
        const TOptional<FString> Message
    )
    {
        this->MessageValue = Message;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithEventAt(
        const TOptional<int64> EventAt
    )
    {
        this->EventAtValue = EventAt;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FEvent::GetEventId() const
    {
        return EventIdValue;
    }
    TOptional<FString> FEvent::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEvent::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<FString> FEvent::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FEvent::GetMessage() const
    {
        return MessageValue;
    }
    TOptional<int64> FEvent::GetEventAt() const
    {
        return EventAtValue;
    }

    FString FEvent::GetEventAtString() const
    {
        if (!EventAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), EventAtValue.GetValue());
    }
    TOptional<int64> FEvent::GetRevision() const
    {
        return RevisionValue;
    }

    FString FEvent::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FEvent::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetStackNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetEventNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FEvent> FEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEvent>()
            ->WithEventId(Data->HasField(ANSI_TO_TCHAR("eventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResourceName(Data->HasField(ANSI_TO_TCHAR("resourceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resourceName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMessage(Data->HasField(ANSI_TO_TCHAR("message")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("message"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEventAt(Data->HasField(ANSI_TO_TCHAR("eventAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("eventAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("eventId", EventIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ResourceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceName", ResourceNameValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (MessageValue.IsSet())
        {
            JsonRootObject->SetStringField("message", MessageValue.GetValue());
        }
        if (EventAtValue.IsSet())
        {
            JsonRootObject->SetStringField("eventAt", FString::Printf(TEXT("%lld"), EventAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FEvent::TypeName = "Event";
}