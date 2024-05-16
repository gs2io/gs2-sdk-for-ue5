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

#include "Gateway/Request/SendNotificationRequest.h"

namespace Gs2::Gateway::Request
{
    FSendNotificationRequest::FSendNotificationRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        SubjectValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>()),
        EnableTransferMobileNotificationValue(TOptional<bool>()),
        SoundValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FSendNotificationRequest::FSendNotificationRequest(
        const FSendNotificationRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        SubjectValue(From.SubjectValue),
        PayloadValue(From.PayloadValue),
        EnableTransferMobileNotificationValue(From.EnableTransferMobileNotificationValue),
        SoundValue(From.SoundValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithSubject(
        const TOptional<FString> Subject
    )
    {
        this->SubjectValue = Subject;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithEnableTransferMobileNotification(
        const TOptional<bool> EnableTransferMobileNotification
    )
    {
        this->EnableTransferMobileNotificationValue = EnableTransferMobileNotification;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithSound(
        const TOptional<FString> Sound
    )
    {
        this->SoundValue = Sound;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSendNotificationRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSendNotificationRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSendNotificationRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSendNotificationRequest::GetSubject() const
    {
        return SubjectValue;
    }

    TOptional<FString> FSendNotificationRequest::GetPayload() const
    {
        return PayloadValue;
    }

    TOptional<bool> FSendNotificationRequest::GetEnableTransferMobileNotification() const
    {
        return EnableTransferMobileNotificationValue;
    }

    FString FSendNotificationRequest::GetEnableTransferMobileNotificationString() const
    {
        if (!EnableTransferMobileNotificationValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableTransferMobileNotificationValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FSendNotificationRequest::GetSound() const
    {
        return SoundValue;
    }

    TOptional<FString> FSendNotificationRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FSendNotificationRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSendNotificationRequest> FSendNotificationRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendNotificationRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSubject(Data->HasField(ANSI_TO_TCHAR("subject")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subject"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEnableTransferMobileNotification(Data->HasField(ANSI_TO_TCHAR("enableTransferMobileNotification")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableTransferMobileNotification"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithSound(Data->HasField(ANSI_TO_TCHAR("sound")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sound"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSendNotificationRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (SubjectValue.IsSet())
        {
            JsonRootObject->SetStringField("subject", SubjectValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        if (EnableTransferMobileNotificationValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableTransferMobileNotification", EnableTransferMobileNotificationValue.GetValue());
        }
        if (SoundValue.IsSet())
        {
            JsonRootObject->SetStringField("sound", SoundValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}