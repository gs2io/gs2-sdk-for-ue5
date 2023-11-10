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

#include "Stamina/Request/UpdateStaminaModelMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FUpdateStaminaModelMasterRequest::FUpdateStaminaModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        InitialCapacityValue(TOptional<int32>()),
        IsOverflowValue(TOptional<bool>()),
        MaxCapacityValue(TOptional<int32>()),
        MaxStaminaTableNameValue(TOptional<FString>()),
        RecoverIntervalTableNameValue(TOptional<FString>()),
        RecoverValueTableNameValue(TOptional<FString>())
    {
    }

    FUpdateStaminaModelMasterRequest::FUpdateStaminaModelMasterRequest(
        const FUpdateStaminaModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        InitialCapacityValue(From.InitialCapacityValue),
        IsOverflowValue(From.IsOverflowValue),
        MaxCapacityValue(From.MaxCapacityValue),
        MaxStaminaTableNameValue(From.MaxStaminaTableNameValue),
        RecoverIntervalTableNameValue(From.RecoverIntervalTableNameValue),
        RecoverValueTableNameValue(From.RecoverValueTableNameValue)
    {
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithIsOverflow(
        const TOptional<bool> IsOverflow
    )
    {
        this->IsOverflowValue = IsOverflow;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithMaxStaminaTableName(
        const TOptional<FString> MaxStaminaTableName
    )
    {
        this->MaxStaminaTableNameValue = MaxStaminaTableName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithRecoverIntervalTableName(
        const TOptional<FString> RecoverIntervalTableName
    )
    {
        this->RecoverIntervalTableNameValue = RecoverIntervalTableName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::WithRecoverValueTableName(
        const TOptional<FString> RecoverValueTableName
    )
    {
        this->RecoverValueTableNameValue = RecoverValueTableName;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateStaminaModelMasterRequest::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FUpdateStaminaModelMasterRequest::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }

    TOptional<int32> FUpdateStaminaModelMasterRequest::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FUpdateStaminaModelMasterRequest::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }

    TOptional<int32> FUpdateStaminaModelMasterRequest::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FUpdateStaminaModelMasterRequest::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }

    TOptional<bool> FUpdateStaminaModelMasterRequest::GetIsOverflow() const
    {
        return IsOverflowValue;
    }

    FString FUpdateStaminaModelMasterRequest::GetIsOverflowString() const
    {
        if (!IsOverflowValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsOverflowValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateStaminaModelMasterRequest::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FUpdateStaminaModelMasterRequest::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetMaxStaminaTableName() const
    {
        return MaxStaminaTableNameValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetRecoverIntervalTableName() const
    {
        return RecoverIntervalTableNameValue;
    }

    TOptional<FString> FUpdateStaminaModelMasterRequest::GetRecoverValueTableName() const
    {
        return RecoverValueTableNameValue;
    }

    TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStaminaModelMasterRequest>()
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
            ->WithStaminaName(Data->HasField("staminaName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("staminaName", v))
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
            ->WithRecoverIntervalMinutes(Data->HasField("recoverIntervalMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("recoverIntervalMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithRecoverValue(Data->HasField("recoverValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("recoverValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithInitialCapacity(Data->HasField("initialCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("initialCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithIsOverflow(Data->HasField("isOverflow") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("isOverflow", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithMaxCapacity(Data->HasField("maxCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maxCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMaxStaminaTableName(Data->HasField("maxStaminaTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("maxStaminaTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRecoverIntervalTableName(Data->HasField("recoverIntervalTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("recoverIntervalTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRecoverValueTableName(Data->HasField("recoverValueTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("recoverValueTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateStaminaModelMasterRequest::ToJson() const
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
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverIntervalMinutes", RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverValue", RecoverValueValue.GetValue());
        }
        if (InitialCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialCapacity", InitialCapacityValue.GetValue());
        }
        if (IsOverflowValue.IsSet())
        {
            JsonRootObject->SetBoolField("isOverflow", IsOverflowValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxCapacity", MaxCapacityValue.GetValue());
        }
        if (MaxStaminaTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("maxStaminaTableName", MaxStaminaTableNameValue.GetValue());
        }
        if (RecoverIntervalTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverIntervalTableName", RecoverIntervalTableNameValue.GetValue());
        }
        if (RecoverValueTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverValueTableName", RecoverValueTableNameValue.GetValue());
        }
        return JsonRootObject;
    }
}