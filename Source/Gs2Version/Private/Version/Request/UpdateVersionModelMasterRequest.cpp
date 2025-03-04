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

#include "Version/Request/UpdateVersionModelMasterRequest.h"

namespace Gs2::Version::Request
{
    FUpdateVersionModelMasterRequest::FUpdateVersionModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        VersionNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        CurrentVersionValue(nullptr),
        WarningVersionValue(nullptr),
        ErrorVersionValue(nullptr),
        ScheduleVersionsValue(nullptr),
        NeedSignatureValue(TOptional<bool>()),
        SignatureKeyIdValue(TOptional<FString>()),
        ApproveRequirementValue(TOptional<FString>())
    {
    }

    FUpdateVersionModelMasterRequest::FUpdateVersionModelMasterRequest(
        const FUpdateVersionModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        VersionNameValue(From.VersionNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ScopeValue(From.ScopeValue),
        TypeValue(From.TypeValue),
        CurrentVersionValue(From.CurrentVersionValue),
        WarningVersionValue(From.WarningVersionValue),
        ErrorVersionValue(From.ErrorVersionValue),
        ScheduleVersionsValue(From.ScheduleVersionsValue),
        NeedSignatureValue(From.NeedSignatureValue),
        SignatureKeyIdValue(From.SignatureKeyIdValue),
        ApproveRequirementValue(From.ApproveRequirementValue)
    {
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithCurrentVersion(
        const TSharedPtr<Model::FVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithWarningVersion(
        const TSharedPtr<Model::FVersion> WarningVersion
    )
    {
        this->WarningVersionValue = WarningVersion;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithErrorVersion(
        const TSharedPtr<Model::FVersion> ErrorVersion
    )
    {
        this->ErrorVersionValue = ErrorVersion;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithScheduleVersions(
        const TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> ScheduleVersions
    )
    {
        this->ScheduleVersionsValue = ScheduleVersions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithNeedSignature(
        const TOptional<bool> NeedSignature
    )
    {
        this->NeedSignatureValue = NeedSignature;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithSignatureKeyId(
        const TOptional<FString> SignatureKeyId
    )
    {
        this->SignatureKeyIdValue = SignatureKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::WithApproveRequirement(
        const TOptional<FString> ApproveRequirement
    )
    {
        this->ApproveRequirementValue = ApproveRequirement;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetVersionName() const
    {
        return VersionNameValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetScope() const
    {
        return ScopeValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetType() const
    {
        return TypeValue;
    }

    TSharedPtr<Model::FVersion> FUpdateVersionModelMasterRequest::GetCurrentVersion() const
    {
        if (!CurrentVersionValue.IsValid())
        {
            return nullptr;
        }
        return CurrentVersionValue;
    }

    TSharedPtr<Model::FVersion> FUpdateVersionModelMasterRequest::GetWarningVersion() const
    {
        if (!WarningVersionValue.IsValid())
        {
            return nullptr;
        }
        return WarningVersionValue;
    }

    TSharedPtr<Model::FVersion> FUpdateVersionModelMasterRequest::GetErrorVersion() const
    {
        if (!ErrorVersionValue.IsValid())
        {
            return nullptr;
        }
        return ErrorVersionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> FUpdateVersionModelMasterRequest::GetScheduleVersions() const
    {
        if (!ScheduleVersionsValue.IsValid())
        {
            return nullptr;
        }
        return ScheduleVersionsValue;
    }

    TOptional<bool> FUpdateVersionModelMasterRequest::GetNeedSignature() const
    {
        return NeedSignatureValue;
    }

    FString FUpdateVersionModelMasterRequest::GetNeedSignatureString() const
    {
        if (!NeedSignatureValue.IsSet())
        {
            return FString("null");
        }
        return FString(NeedSignatureValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetSignatureKeyId() const
    {
        return SignatureKeyIdValue;
    }

    TOptional<FString> FUpdateVersionModelMasterRequest::GetApproveRequirement() const
    {
        return ApproveRequirementValue;
    }

    TSharedPtr<FUpdateVersionModelMasterRequest> FUpdateVersionModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateVersionModelMasterRequest>()
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
            ->WithVersionName(Data->HasField(ANSI_TO_TCHAR("versionName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("versionName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScope(Data->HasField(ANSI_TO_TCHAR("scope")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scope"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithCurrentVersion(Data->HasField(ANSI_TO_TCHAR("currentVersion")) ? [Data]() -> Model::FVersionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("currentVersion")))
                  {
                      return nullptr;
                  }
                  return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("currentVersion")));
              }() : nullptr)
          ->WithWarningVersion(Data->HasField(ANSI_TO_TCHAR("warningVersion")) ? [Data]() -> Model::FVersionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("warningVersion")))
                  {
                      return nullptr;
                  }
                  return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("warningVersion")));
              }() : nullptr)
          ->WithErrorVersion(Data->HasField(ANSI_TO_TCHAR("errorVersion")) ? [Data]() -> Model::FVersionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("errorVersion")))
                  {
                      return nullptr;
                  }
                  return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("errorVersion")));
              }() : nullptr)
          ->WithScheduleVersions(Data->HasField(ANSI_TO_TCHAR("scheduleVersions")) ? [Data]() -> TSharedPtr<TArray<Model::FScheduleVersionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FScheduleVersionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("scheduleVersions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("scheduleVersions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("scheduleVersions")))
                      {
                          v->Add(Model::FScheduleVersion::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FScheduleVersionPtr>>())
            ->WithNeedSignature(Data->HasField(ANSI_TO_TCHAR("needSignature")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("needSignature"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithSignatureKeyId(Data->HasField(ANSI_TO_TCHAR("signatureKeyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signatureKeyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithApproveRequirement(Data->HasField(ANSI_TO_TCHAR("approveRequirement")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("approveRequirement"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateVersionModelMasterRequest::ToJson() const
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
        if (VersionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("versionName", VersionNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (CurrentVersionValue != nullptr && CurrentVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("currentVersion", CurrentVersionValue->ToJson());
        }
        if (WarningVersionValue != nullptr && WarningVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("warningVersion", WarningVersionValue->ToJson());
        }
        if (ErrorVersionValue != nullptr && ErrorVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorVersion", ErrorVersionValue->ToJson());
        }
        if (ScheduleVersionsValue != nullptr && ScheduleVersionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ScheduleVersionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("scheduleVersions", v);
        }
        if (NeedSignatureValue.IsSet())
        {
            JsonRootObject->SetBoolField("needSignature", NeedSignatureValue.GetValue());
        }
        if (SignatureKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("signatureKeyId", SignatureKeyIdValue.GetValue());
        }
        if (ApproveRequirementValue.IsSet())
        {
            JsonRootObject->SetStringField("approveRequirement", ApproveRequirementValue.GetValue());
        }
        return JsonRootObject;
    }
}