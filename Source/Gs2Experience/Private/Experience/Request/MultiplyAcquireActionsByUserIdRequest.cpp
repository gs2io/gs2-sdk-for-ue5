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

#include "Experience/Request/MultiplyAcquireActionsByUserIdRequest.h"

namespace Gs2::Experience::Request
{
    FMultiplyAcquireActionsByUserIdRequest::FMultiplyAcquireActionsByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ExperienceNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        AcquireActionsValue(nullptr),
        BaseRateValue(TOptional<float>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FMultiplyAcquireActionsByUserIdRequest::FMultiplyAcquireActionsByUserIdRequest(
        const FMultiplyAcquireActionsByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        ExperienceNameValue(From.ExperienceNameValue),
        PropertyIdValue(From.PropertyIdValue),
        RateNameValue(From.RateNameValue),
        AcquireActionsValue(From.AcquireActionsValue),
        BaseRateValue(From.BaseRateValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithExperienceName(
        const TOptional<FString> ExperienceName
    )
    {
        this->ExperienceNameValue = ExperienceName;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithBaseRate(
        const TOptional<float> BaseRate
    )
    {
        this->BaseRateValue = BaseRate;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetExperienceName() const
    {
        return ExperienceNameValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FMultiplyAcquireActionsByUserIdRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TOptional<float> FMultiplyAcquireActionsByUserIdRequest::GetBaseRate() const
    {
        return BaseRateValue;
    }

    FString FMultiplyAcquireActionsByUserIdRequest::GetBaseRateString() const
    {
        if (!BaseRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BaseRateValue.GetValue());
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FMultiplyAcquireActionsByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FMultiplyAcquireActionsByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMultiplyAcquireActionsByUserIdRequest>()
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
            ->WithExperienceName(Data->HasField(ANSI_TO_TCHAR("experienceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("experienceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField(ANSI_TO_TCHAR("propertyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRateName(Data->HasField(ANSI_TO_TCHAR("rateName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rateName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithBaseRate(Data->HasField(ANSI_TO_TCHAR("baseRate")) ? [Data]() -> TOptional<float>
              {
                  float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("baseRate"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<float>();
              }() : TOptional<float>())
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

    TSharedPtr<FJsonObject> FMultiplyAcquireActionsByUserIdRequest::ToJson() const
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
        if (ExperienceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceName", ExperienceNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        if (BaseRateValue.IsSet())
        {
            JsonRootObject->SetNumberField("baseRate", BaseRateValue.GetValue());
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