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

#include "Enchant/Request/VerifyRarityParameterStatusByUserIdRequest.h"

namespace Gs2::Enchant::Request
{
    FVerifyRarityParameterStatusByUserIdRequest::FVerifyRarityParameterStatusByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        ParameterValueNameValue(TOptional<FString>()),
        ParameterCountValue(TOptional<int32>())
    {
    }

    FVerifyRarityParameterStatusByUserIdRequest::FVerifyRarityParameterStatusByUserIdRequest(
        const FVerifyRarityParameterStatusByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ParameterNameValue(From.ParameterNameValue),
        UserIdValue(From.UserIdValue),
        PropertyIdValue(From.PropertyIdValue),
        VerifyTypeValue(From.VerifyTypeValue),
        ParameterValueNameValue(From.ParameterValueNameValue),
        ParameterCountValue(From.ParameterCountValue)
    {
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithParameterValueName(
        const TOptional<FString> ParameterValueName
    )
    {
        this->ParameterValueNameValue = ParameterValueName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithParameterCount(
        const TOptional<int32> ParameterCount
    )
    {
        this->ParameterCountValue = ParameterCount;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetParameterValueName() const
    {
        return ParameterValueNameValue;
    }

    TOptional<int32> FVerifyRarityParameterStatusByUserIdRequest::GetParameterCount() const
    {
        return ParameterCountValue;
    }

    FString FVerifyRarityParameterStatusByUserIdRequest::GetParameterCountString() const
    {
        if (!ParameterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ParameterCountValue.GetValue());
    }

    TOptional<FString> FVerifyRarityParameterStatusByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FVerifyRarityParameterStatusByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyRarityParameterStatusByUserIdRequest>()
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
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("parameterName", v))
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
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField("verifyType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("verifyType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithParameterValueName(Data->HasField("parameterValueName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("parameterValueName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithParameterCount(Data->HasField("parameterCount") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("parameterCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyRarityParameterStatusByUserIdRequest::ToJson() const
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
        if (ParameterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterName", ParameterNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (ParameterValueNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterValueName", ParameterValueNameValue.GetValue());
        }
        if (ParameterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("parameterCount", ParameterCountValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}