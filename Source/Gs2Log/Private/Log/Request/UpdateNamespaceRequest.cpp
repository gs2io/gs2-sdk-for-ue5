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

#include "Log/Request/UpdateNamespaceRequest.h"

namespace Gs2::Log::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        GcpCredentialJsonValue(TOptional<FString>()),
        BigQueryDatasetNameValue(TOptional<FString>()),
        LogExpireDaysValue(TOptional<int32>()),
        AwsRegionValue(TOptional<FString>()),
        AwsAccessKeyIdValue(TOptional<FString>()),
        AwsSecretAccessKeyValue(TOptional<FString>()),
        FirehoseStreamNameValue(TOptional<FString>()),
        FirehoseCompressDataValue(TOptional<FString>())
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        TypeValue(From.TypeValue),
        GcpCredentialJsonValue(From.GcpCredentialJsonValue),
        BigQueryDatasetNameValue(From.BigQueryDatasetNameValue),
        LogExpireDaysValue(From.LogExpireDaysValue),
        AwsRegionValue(From.AwsRegionValue),
        AwsAccessKeyIdValue(From.AwsAccessKeyIdValue),
        AwsSecretAccessKeyValue(From.AwsSecretAccessKeyValue),
        FirehoseStreamNameValue(From.FirehoseStreamNameValue),
        FirehoseCompressDataValue(From.FirehoseCompressDataValue)
    {
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithGcpCredentialJson(
        const TOptional<FString> GcpCredentialJson
    )
    {
        this->GcpCredentialJsonValue = GcpCredentialJson;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithBigQueryDatasetName(
        const TOptional<FString> BigQueryDatasetName
    )
    {
        this->BigQueryDatasetNameValue = BigQueryDatasetName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLogExpireDays(
        const TOptional<int32> LogExpireDays
    )
    {
        this->LogExpireDaysValue = LogExpireDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAwsRegion(
        const TOptional<FString> AwsRegion
    )
    {
        this->AwsRegionValue = AwsRegion;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAwsAccessKeyId(
        const TOptional<FString> AwsAccessKeyId
    )
    {
        this->AwsAccessKeyIdValue = AwsAccessKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAwsSecretAccessKey(
        const TOptional<FString> AwsSecretAccessKey
    )
    {
        this->AwsSecretAccessKeyValue = AwsSecretAccessKey;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithFirehoseStreamName(
        const TOptional<FString> FirehoseStreamName
    )
    {
        this->FirehoseStreamNameValue = FirehoseStreamName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithFirehoseCompressData(
        const TOptional<FString> FirehoseCompressData
    )
    {
        this->FirehoseCompressDataValue = FirehoseCompressData;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetType() const
    {
        return TypeValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetGcpCredentialJson() const
    {
        return GcpCredentialJsonValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetBigQueryDatasetName() const
    {
        return BigQueryDatasetNameValue;
    }

    TOptional<int32> FUpdateNamespaceRequest::GetLogExpireDays() const
    {
        return LogExpireDaysValue;
    }

    FString FUpdateNamespaceRequest::GetLogExpireDaysString() const
    {
        if (!LogExpireDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LogExpireDaysValue.GetValue());
    }

    TOptional<FString> FUpdateNamespaceRequest::GetAwsRegion() const
    {
        return AwsRegionValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetAwsAccessKeyId() const
    {
        return AwsAccessKeyIdValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetAwsSecretAccessKey() const
    {
        return AwsSecretAccessKeyValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetFirehoseStreamName() const
    {
        return FirehoseStreamNameValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetFirehoseCompressData() const
    {
        return FirehoseCompressDataValue;
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateNamespaceRequest>()
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
              }() : TOptional<FString>())
            ->WithFirehoseCompressData(Data->HasField(ANSI_TO_TCHAR("firehoseCompressData")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("firehoseCompressData"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateNamespaceRequest::ToJson() const
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
        if (FirehoseCompressDataValue.IsSet())
        {
            JsonRootObject->SetStringField("firehoseCompressData", FirehoseCompressDataValue.GetValue());
        }
        return JsonRootObject;
    }
}