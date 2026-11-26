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

#include "Formation/Request/VerifyFormByUserIdRequest.h"

namespace Gs2::Formation::Request
{
    FVerifyFormByUserIdRequest::FVerifyFormByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MoldModelNameValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        SlotNameValue(TOptional<FString>()),
        PropertyIdRegexValue(TOptional<FString>()),
        CountTypeValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        CountValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FVerifyFormByUserIdRequest::FVerifyFormByUserIdRequest(
        const FVerifyFormByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        MoldModelNameValue(From.MoldModelNameValue),
        IndexValue(From.IndexValue),
        SlotNameValue(From.SlotNameValue),
        PropertyIdRegexValue(From.PropertyIdRegexValue),
        CountTypeValue(From.CountTypeValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CountValue(From.CountValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithMoldModelName(
        const TOptional<FString> MoldModelName
    )
    {
        this->MoldModelNameValue = MoldModelName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithSlotName(
        const TOptional<FString> SlotName
    )
    {
        this->SlotNameValue = SlotName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithPropertyIdRegex(
        const TOptional<FString> PropertyIdRegex
    )
    {
        this->PropertyIdRegexValue = PropertyIdRegex;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithCountType(
        const TOptional<FString> CountType
    )
    {
        this->CountTypeValue = CountType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetMoldModelName() const
    {
        return MoldModelNameValue;
    }

    TOptional<int32> FVerifyFormByUserIdRequest::GetIndex() const
    {
        return IndexValue;
    }

    FString FVerifyFormByUserIdRequest::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetSlotName() const
    {
        return SlotNameValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetPropertyIdRegex() const
    {
        return PropertyIdRegexValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetCountType() const
    {
        return CountTypeValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyFormByUserIdRequest::GetCount() const
    {
        return CountValue;
    }

    FString FVerifyFormByUserIdRequest::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FVerifyFormByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyFormByUserIdRequest>()
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
            ->WithMoldModelName(Data->HasField(ANSI_TO_TCHAR("moldModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("moldModelName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIndex(Data->HasField(ANSI_TO_TCHAR("index")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("index"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithSlotName(Data->HasField(ANSI_TO_TCHAR("slotName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("slotName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyIdRegex(Data->HasField(ANSI_TO_TCHAR("propertyIdRegex")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyIdRegex"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCountType(Data->HasField(ANSI_TO_TCHAR("countType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("countType"), v))
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
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FVerifyFormByUserIdRequest::ToJson() const
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
        if (MoldModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("moldModelName"), MoldModelNameValue.GetValue());
        }
        if (IndexValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("index"), IndexValue.GetValue());
        }
        if (SlotNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("slotName"), SlotNameValue.GetValue());
        }
        if (PropertyIdRegexValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("propertyIdRegex"), PropertyIdRegexValue.GetValue());
        }
        if (CountTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("countType"), CountTypeValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyType"), VerifyTypeValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("count"), CountValue.GetValue());
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