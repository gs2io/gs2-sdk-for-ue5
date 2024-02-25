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

#include "Experience/Request/AddExperienceByUserIdRequest.h"

namespace Gs2::Experience::Request
{
    FAddExperienceByUserIdRequest::FAddExperienceByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ExperienceNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ExperienceValueValue(TOptional<int64>()),
        TruncateExperienceWhenRankUpValue(TOptional<bool>())
    {
    }

    FAddExperienceByUserIdRequest::FAddExperienceByUserIdRequest(
        const FAddExperienceByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        ExperienceNameValue(From.ExperienceNameValue),
        PropertyIdValue(From.PropertyIdValue),
        ExperienceValueValue(From.ExperienceValueValue),
        TruncateExperienceWhenRankUpValue(From.TruncateExperienceWhenRankUpValue)
    {
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithExperienceName(
        const TOptional<FString> ExperienceName
    )
    {
        this->ExperienceNameValue = ExperienceName;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithExperienceValue(
        const TOptional<int64> ExperienceValue
    )
    {
        this->ExperienceValueValue = ExperienceValue;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithTruncateExperienceWhenRankUp(
        const TOptional<bool> TruncateExperienceWhenRankUp
    )
    {
        this->TruncateExperienceWhenRankUpValue = TruncateExperienceWhenRankUp;
        return SharedThis(this);
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetExperienceName() const
    {
        return ExperienceNameValue;
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<int64> FAddExperienceByUserIdRequest::GetExperienceValue() const
    {
        return ExperienceValueValue;
    }

    FString FAddExperienceByUserIdRequest::GetExperienceValueString() const
    {
        if (!ExperienceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExperienceValueValue.GetValue());
    }

    TOptional<bool> FAddExperienceByUserIdRequest::GetTruncateExperienceWhenRankUp() const
    {
        return TruncateExperienceWhenRankUpValue;
    }

    FString FAddExperienceByUserIdRequest::GetTruncateExperienceWhenRankUpString() const
    {
        if (!TruncateExperienceWhenRankUpValue.IsSet())
        {
            return FString("null");
        }
        return FString(TruncateExperienceWhenRankUpValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FAddExperienceByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FAddExperienceByUserIdRequest> FAddExperienceByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddExperienceByUserIdRequest>()
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
            ->WithExperienceName(Data->HasField("experienceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("experienceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithExperienceValue(Data->HasField("experienceValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("experienceValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithTruncateExperienceWhenRankUp(Data->HasField("truncateExperienceWhenRankUp") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("truncateExperienceWhenRankUp", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAddExperienceByUserIdRequest::ToJson() const
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
        if (ExperienceValueValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceValue", FString::Printf(TEXT("%lld"), ExperienceValueValue.GetValue()));
        }
        if (TruncateExperienceWhenRankUpValue.IsSet())
        {
            JsonRootObject->SetBoolField("truncateExperienceWhenRankUp", TruncateExperienceWhenRankUpValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}