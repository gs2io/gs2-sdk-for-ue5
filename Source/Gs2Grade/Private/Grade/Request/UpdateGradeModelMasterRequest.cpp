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

#include "Grade/Request/UpdateGradeModelMasterRequest.h"

namespace Gs2::Grade::Request
{
    FUpdateGradeModelMasterRequest::FUpdateGradeModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        GradeNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultGradesValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        GradeEntriesValue(nullptr),
        AcquireActionRatesValue(nullptr)
    {
    }

    FUpdateGradeModelMasterRequest::FUpdateGradeModelMasterRequest(
        const FUpdateGradeModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GradeNameValue(From.GradeNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultGradesValue(From.DefaultGradesValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        GradeEntriesValue(From.GradeEntriesValue),
        AcquireActionRatesValue(From.AcquireActionRatesValue)
    {
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithGradeName(
        const TOptional<FString> GradeName
    )
    {
        this->GradeNameValue = GradeName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithDefaultGrades(
        const TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGrades
    )
    {
        this->DefaultGradesValue = DefaultGrades;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithGradeEntries(
        const TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntries
    )
    {
        this->GradeEntriesValue = GradeEntries;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetGradeName() const
    {
        return GradeNameValue;
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> FUpdateGradeModelMasterRequest::GetDefaultGrades() const
    {
        if (!DefaultGradesValue.IsValid())
        {
            return nullptr;
        }
        return DefaultGradesValue;
    }

    TOptional<FString> FUpdateGradeModelMasterRequest::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> FUpdateGradeModelMasterRequest::GetGradeEntries() const
    {
        if (!GradeEntriesValue.IsValid())
        {
            return nullptr;
        }
        return GradeEntriesValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> FUpdateGradeModelMasterRequest::GetAcquireActionRates() const
    {
        if (!AcquireActionRatesValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionRatesValue;
    }

    TSharedPtr<FUpdateGradeModelMasterRequest> FUpdateGradeModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGradeModelMasterRequest>()
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
            ->WithGradeName(Data->HasField("gradeName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("gradeName", v))
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
          ->WithDefaultGrades(Data->HasField("defaultGrades") ? [Data]() -> TSharedPtr<TArray<Model::FDefaultGradeModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FDefaultGradeModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("defaultGrades") && Data->HasTypedField<EJson::Array>("defaultGrades"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("defaultGrades"))
                      {
                          v->Add(Model::FDefaultGradeModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGradeEntries(Data->HasField("gradeEntries") ? [Data]() -> TSharedPtr<TArray<Model::FGradeEntryModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FGradeEntryModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("gradeEntries") && Data->HasTypedField<EJson::Array>("gradeEntries"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("gradeEntries"))
                      {
                          v->Add(Model::FGradeEntryModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithAcquireActionRates(Data->HasField("acquireActionRates") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionRatePtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionRatePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("acquireActionRates") && Data->HasTypedField<EJson::Array>("acquireActionRates"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("acquireActionRates"))
                      {
                          v->Add(Model::FAcquireActionRate::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateGradeModelMasterRequest::ToJson() const
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
        if (GradeNameValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeName", GradeNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DefaultGradesValue != nullptr && DefaultGradesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DefaultGradesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("defaultGrades", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (GradeEntriesValue != nullptr && GradeEntriesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GradeEntriesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("gradeEntries", v);
        }
        if (AcquireActionRatesValue != nullptr && AcquireActionRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActionRates", v);
        }
        return JsonRootObject;
    }
}