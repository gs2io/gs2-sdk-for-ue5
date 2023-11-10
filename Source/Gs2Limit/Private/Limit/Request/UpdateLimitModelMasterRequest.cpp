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

#include "Limit/Request/UpdateLimitModelMasterRequest.h"

namespace Gs2::Limit::Request
{
    FUpdateLimitModelMasterRequest::FUpdateLimitModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        LimitNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>())
    {
    }

    FUpdateLimitModelMasterRequest::FUpdateLimitModelMasterRequest(
        const FUpdateLimitModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LimitNameValue(From.LimitNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue)
    {
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetLimitName() const
    {
        return LimitNameValue;
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetResetType() const
    {
        return ResetTypeValue;
    }

    TOptional<int32> FUpdateLimitModelMasterRequest::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FUpdateLimitModelMasterRequest::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }

    TOptional<FString> FUpdateLimitModelMasterRequest::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }

    TOptional<int32> FUpdateLimitModelMasterRequest::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FUpdateLimitModelMasterRequest::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    TSharedPtr<FUpdateLimitModelMasterRequest> FUpdateLimitModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateLimitModelMasterRequest>()
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
            ->WithLimitName(Data->HasField("limitName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("limitName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetType(Data->HasField("resetType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("resetType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetDayOfMonth(Data->HasField("resetDayOfMonth") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("resetDayOfMonth", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithResetDayOfWeek(Data->HasField("resetDayOfWeek") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("resetDayOfWeek", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetHour(Data->HasField("resetHour") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("resetHour", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUpdateLimitModelMasterRequest::ToJson() const
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
        if (LimitNameValue.IsSet())
        {
            JsonRootObject->SetStringField("limitName", LimitNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ResetDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetDayOfMonth", ResetDayOfMonthValue.GetValue());
        }
        if (ResetDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("resetDayOfWeek", ResetDayOfWeekValue.GetValue());
        }
        if (ResetHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetHour", ResetHourValue.GetValue());
        }
        return JsonRootObject;
    }
}