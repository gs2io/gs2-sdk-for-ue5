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

#include "Exchange/Request/SkipByUserIdRequest.h"

namespace Gs2::Exchange::Request
{
    FSkipByUserIdRequest::FSkipByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AwaitNameValue(TOptional<FString>()),
        SkipTypeValue(TOptional<FString>()),
        MinutesValue(TOptional<int32>()),
        RateValue(TOptional<float>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FSkipByUserIdRequest::FSkipByUserIdRequest(
        const FSkipByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        AwaitNameValue(From.AwaitNameValue),
        SkipTypeValue(From.SkipTypeValue),
        MinutesValue(From.MinutesValue),
        RateValue(From.RateValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithAwaitName(
        const TOptional<FString> AwaitName
    )
    {
        this->AwaitNameValue = AwaitName;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithSkipType(
        const TOptional<FString> SkipType
    )
    {
        this->SkipTypeValue = SkipType;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithMinutes(
        const TOptional<int32> Minutes
    )
    {
        this->MinutesValue = Minutes;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSkipByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSkipByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSkipByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSkipByUserIdRequest::GetAwaitName() const
    {
        return AwaitNameValue;
    }

    TOptional<FString> FSkipByUserIdRequest::GetSkipType() const
    {
        return SkipTypeValue;
    }

    TOptional<int32> FSkipByUserIdRequest::GetMinutes() const
    {
        return MinutesValue;
    }

    FString FSkipByUserIdRequest::GetMinutesString() const
    {
        if (!MinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinutesValue.GetValue());
    }

    TOptional<float> FSkipByUserIdRequest::GetRate() const
    {
        return RateValue;
    }

    FString FSkipByUserIdRequest::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    TOptional<FString> FSkipByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FSkipByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSkipByUserIdRequest> FSkipByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSkipByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAwaitName(Data->HasField("awaitName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("awaitName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSkipType(Data->HasField("skipType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("skipType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMinutes(Data->HasField("minutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("minutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithRate(Data->HasField("rate") ? [Data]() -> TOptional<float>
              {
                  float v;
                    if (Data->TryGetNumberField("rate", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<float>();
              }() : TOptional<float>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSkipByUserIdRequest::ToJson() const
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
        if (AwaitNameValue.IsSet())
        {
            JsonRootObject->SetStringField("awaitName", AwaitNameValue.GetValue());
        }
        if (SkipTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("skipType", SkipTypeValue.GetValue());
        }
        if (MinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("minutes", MinutesValue.GetValue());
        }
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
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