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

#include "AdReward/Request/VerifyPointRequest.h"

namespace Gs2::AdReward::Request
{
    FVerifyPointRequest::FVerifyPointRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        PointValue(TOptional<int64>()),
        MultiplyValueSpecifyingQuantityValue(TOptional<bool>())
    {
    }

    FVerifyPointRequest::FVerifyPointRequest(
        const FVerifyPointRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        VerifyTypeValue(From.VerifyTypeValue),
        PointValue(From.PointValue),
        MultiplyValueSpecifyingQuantityValue(From.MultiplyValueSpecifyingQuantityValue)
    {
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithPoint(
        const TOptional<int64> Point
    )
    {
        this->PointValue = Point;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithMultiplyValueSpecifyingQuantity(
        const TOptional<bool> MultiplyValueSpecifyingQuantity
    )
    {
        this->MultiplyValueSpecifyingQuantityValue = MultiplyValueSpecifyingQuantity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyPointRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyPointRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyPointRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyPointRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int64> FVerifyPointRequest::GetPoint() const
    {
        return PointValue;
    }

    FString FVerifyPointRequest::GetPointString() const
    {
        if (!PointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), PointValue.GetValue());
    }

    TOptional<bool> FVerifyPointRequest::GetMultiplyValueSpecifyingQuantity() const
    {
        return MultiplyValueSpecifyingQuantityValue;
    }

    FString FVerifyPointRequest::GetMultiplyValueSpecifyingQuantityString() const
    {
        if (!MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString(MultiplyValueSpecifyingQuantityValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FVerifyPointRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyPointRequest> FVerifyPointRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyPointRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPoint(Data->HasField(ANSI_TO_TCHAR("point")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("point"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMultiplyValueSpecifyingQuantity(Data->HasField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyPointRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contextStack"), ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceName"), NamespaceNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("xGs2AccessToken"), AccessTokenValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyType"), VerifyTypeValue.GetValue());
        }
        if (PointValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("point"), FString::Printf(TEXT("%lld"), PointValue.GetValue()));
        }
        if (MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("multiplyValueSpecifyingQuantity"), MultiplyValueSpecifyingQuantityValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}