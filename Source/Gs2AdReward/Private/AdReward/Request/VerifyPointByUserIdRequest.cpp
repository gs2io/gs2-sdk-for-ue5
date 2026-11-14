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

#include "AdReward/Request/VerifyPointByUserIdRequest.h"

namespace Gs2::AdReward::Request
{
    FVerifyPointByUserIdRequest::FVerifyPointByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        PointValue(TOptional<int64>()),
        MultiplyValueSpecifyingQuantityValue(TOptional<bool>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FVerifyPointByUserIdRequest::FVerifyPointByUserIdRequest(
        const FVerifyPointByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        VerifyTypeValue(From.VerifyTypeValue),
        PointValue(From.PointValue),
        MultiplyValueSpecifyingQuantityValue(From.MultiplyValueSpecifyingQuantityValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithPoint(
        const TOptional<int64> Point
    )
    {
        this->PointValue = Point;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithMultiplyValueSpecifyingQuantity(
        const TOptional<bool> MultiplyValueSpecifyingQuantity
    )
    {
        this->MultiplyValueSpecifyingQuantityValue = MultiplyValueSpecifyingQuantity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int64> FVerifyPointByUserIdRequest::GetPoint() const
    {
        return PointValue;
    }

    FString FVerifyPointByUserIdRequest::GetPointString() const
    {
        if (!PointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), PointValue.GetValue());
    }

    TOptional<bool> FVerifyPointByUserIdRequest::GetMultiplyValueSpecifyingQuantity() const
    {
        return MultiplyValueSpecifyingQuantityValue;
    }

    FString FVerifyPointByUserIdRequest::GetMultiplyValueSpecifyingQuantityString() const
    {
        if (!MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString(MultiplyValueSpecifyingQuantityValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FVerifyPointByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyPointByUserIdRequest> FVerifyPointByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyPointByUserIdRequest>()
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
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
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyPointByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
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
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("timeOffsetToken"), TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}