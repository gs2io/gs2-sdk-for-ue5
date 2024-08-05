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

#include "Log/Request/CreateNamespaceRequest.h"

namespace Gs2::Log::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        GcpCredentialJsonValue(TOptional<FString>()),
        BigQueryDatasetNameValue(TOptional<FString>()),
        LogExpireDaysValue(TOptional<int32>()),
        AwsRegionValue(TOptional<FString>()),
        AwsAccessKeyIdValue(TOptional<FString>()),
        AwsSecretAccessKeyValue(TOptional<FString>()),
        FirehoseStreamNameValue(TOptional<FString>())
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TypeValue(From.TypeValue),
        GcpCredentialJsonValue(From.GcpCredentialJsonValue),
        BigQueryDatasetNameValue(From.BigQueryDatasetNameValue),
        LogExpireDaysValue(From.LogExpireDaysValue),
        AwsRegionValue(From.AwsRegionValue),
        AwsAccessKeyIdValue(From.AwsAccessKeyIdValue),
        AwsSecretAccessKeyValue(From.AwsSecretAccessKeyValue),
        FirehoseStreamNameValue(From.FirehoseStreamNameValue)
    {
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithGcpCredentialJson(
        const TOptional<FString> GcpCredentialJson
    )
    {
        this->GcpCredentialJsonValue = GcpCredentialJson;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithBigQueryDatasetName(
        const TOptional<FString> BigQueryDatasetName
    )
    {
        this->BigQueryDatasetNameValue = BigQueryDatasetName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLogExpireDays(
        const TOptional<int32> LogExpireDays
    )
    {
        this->LogExpireDaysValue = LogExpireDays;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAwsRegion(
        const TOptional<FString> AwsRegion
    )
    {
        this->AwsRegionValue = AwsRegion;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAwsAccessKeyId(
        const TOptional<FString> AwsAccessKeyId
    )
    {
        this->AwsAccessKeyIdValue = AwsAccessKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAwsSecretAccessKey(
        const TOptional<FString> AwsSecretAccessKey
    )
    {
        this->AwsSecretAccessKeyValue = AwsSecretAccessKey;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithFirehoseStreamName(
        const TOptional<FString> FirehoseStreamName
    )
    {
        this->FirehoseStreamNameValue = FirehoseStreamName;
        return SharedThis(this);
    }

    TOptional<FString> FCreateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetType() const
    {
        return TypeValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetGcpCredentialJson() const
    {
        return GcpCredentialJsonValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetBigQueryDatasetName() const
    {
        return BigQueryDatasetNameValue;
    }

    TOptional<int32> FCreateNamespaceRequest::GetLogExpireDays() const
    {
        return LogExpireDaysValue;
    }

    FString FCreateNamespaceRequest::GetLogExpireDaysString() const
    {
        if (!LogExpireDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LogExpireDaysValue.GetValue());
    }

    TOptional<FString> FCreateNamespaceRequest::GetAwsRegion() const
    {
        return AwsRegionValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetAwsAccessKeyId() const
    {
        return AwsAccessKeyIdValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetAwsSecretAccessKey() const
    {
        return AwsSecretAccessKeyValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetFirehoseStreamName() const
    {
        return FirehoseStreamNameValue;
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateNamespaceRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGcpCredentialJson(Data->HasField(ANSI_TO_TCHAR("gcpCredentialJson")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gcpCredentialJson"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBigQueryDatasetName(Data->HasField(ANSI_TO_TCHAR("bigQueryDatasetName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("bigQueryDatasetName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLogExpireDays(Data->HasField(ANSI_TO_TCHAR("logExpireDays")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("logExpireDays"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAwsRegion(Data->HasField(ANSI_TO_TCHAR("awsRegion")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsRegion"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAwsAccessKeyId(Data->HasField(ANSI_TO_TCHAR("awsAccessKeyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsAccessKeyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAwsSecretAccessKey(Data->HasField(ANSI_TO_TCHAR("awsSecretAccessKey")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("awsSecretAccessKey"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithFirehoseStreamName(Data->HasField(ANSI_TO_TCHAR("firehoseStreamName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("firehoseStreamName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (GcpCredentialJsonValue.IsSet())
        {
            JsonRootObject->SetStringField("gcpCredentialJson", GcpCredentialJsonValue.GetValue());
        }
        if (BigQueryDatasetNameValue.IsSet())
        {
            JsonRootObject->SetStringField("bigQueryDatasetName", BigQueryDatasetNameValue.GetValue());
        }
        if (LogExpireDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("logExpireDays", LogExpireDaysValue.GetValue());
        }
        if (AwsRegionValue.IsSet())
        {
            JsonRootObject->SetStringField("awsRegion", AwsRegionValue.GetValue());
        }
        if (AwsAccessKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("awsAccessKeyId", AwsAccessKeyIdValue.GetValue());
        }
        if (AwsSecretAccessKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("awsSecretAccessKey", AwsSecretAccessKeyValue.GetValue());
        }
        if (FirehoseStreamNameValue.IsSet())
        {
            JsonRootObject->SetStringField("firehoseStreamName", FirehoseStreamNameValue.GetValue());
        }
        return JsonRootObject;
    }
}