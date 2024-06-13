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
 *
 * deny overwrite
 */

#include "Datastore/Domain/Model/Gs2DatastoreEzUserGameSessionDomain.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzUserGameSessionDomain::FileUrl() const
    {
        return Domain->FileUrl;
    }

    TOptional<int64> FEzUserGameSessionDomain::ContentLength() const
    {
        return Domain->ContentLength;
    }

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Datastore::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FPrepareUploadTask::FPrepareUploadTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        TOptional<FString> Name,
        TOptional<FString> Scope,
        TOptional<FString> ContentType,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<bool> UpdateIfExists
    ): Self(Self), Name(Name), Scope(Scope), ContentType(ContentType), AllowUserIds(AllowUserIds), UpdateIfExists(UpdateIfExists)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FPrepareUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PrepareUpload(
                    MakeShared<Gs2::Datastore::Request::FPrepareUploadRequest>()
                        ->WithName(Name)
                        ->WithScope(Scope)
                        ->WithContentType(ContentType)
                        ->WithAllowUserIds([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            if (!AllowUserIds.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *AllowUserIds) {
                                Arr->Add(Value);
                            }
                            return Arr;
                        }())
                        ->WithUpdateIfExists(UpdateIfExists)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FPrepareUploadTask>> FEzUserGameSessionDomain::PrepareUpload(
        TOptional<FString> Name,
        TOptional<FString> Scope,
        TOptional<FString> ContentType,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<bool> UpdateIfExists
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareUploadTask>>(
            this->AsShared(),
            Name,
            Scope,
            ContentType,
            AllowUserIds,
            UpdateIfExists
        );
    }

    FEzUserGameSessionDomain::FPrepareDownloadTask::FPrepareDownloadTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString DataObjectId
    ): Self(Self), DataObjectId(DataObjectId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FPrepareDownloadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PrepareDownload(
                    MakeShared<Gs2::Datastore::Request::FPrepareDownloadRequest>()
                        ->WithDataObjectId(DataObjectId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FPrepareDownloadTask>> FEzUserGameSessionDomain::PrepareDownload(
        FString DataObjectId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadTask>>(
            this->AsShared(),
            DataObjectId
        );
    }

    Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectsIteratorPtr FEzUserGameSessionDomain::DataObjects(
          const TOptional<FString> Status
    ) const
    {
        return MakeShared<Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            Status
        );
    }

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomainPtr FEzUserGameSessionDomain::DataObject(
        const FString DataObjectName
    ) const
    {
        return MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
            Domain->DataObject(
                DataObjectName
            ),
            GameSession,
            ConnectionValue
        );
    }
    
    FEzUserGameSessionDomain::FUploadTask::FUploadTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        TArray<uint8> Binary,
        TOptional<FString> Name,
        TOptional<FString> Scope,
        TOptional<FString> ContentType,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<bool> UpdateIfExists
    ): Self(Self), Binary(Binary), Name(Name), Scope(Scope), ContentType(ContentType), AllowUserIds(AllowUserIds), UpdateIfExists(UpdateIfExists)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                FString Url("");
                FString DataObjectName("");
                {
                    const auto Task = Self->Domain->PrepareUpload(
                        MakeShared<Gs2::Datastore::Request::FPrepareUploadRequest>()
                            ->WithName(Name)
                            ->WithScope(Scope)
                            ->WithContentType(ContentType)
                            ->WithAllowUserIds([&]{
                                auto Arr = MakeShared<TArray<FString>>();
                                if (!AllowUserIds.IsSet()) {
                                    return Arr;
                                }
                                for (auto Value : *AllowUserIds) {
                                    Arr->Add(Value);
                                }
                                return Arr;
                            }())
                            ->WithUpdateIfExists(UpdateIfExists)
                    );
                    Task->StartSynchronousTask();
                    if (Task->GetTask().IsError())
                    {
                        Task->EnsureCompletion();
                        return Task->GetTask().Error();
                    }
                    Url = *Task->GetTask().Result()->GetUploadUrl();
                    Task->EnsureCompletion();

                    const auto Task2 = Task->GetTask().Result()->Model();
                    Task2->StartSynchronousTask();
                    if (Task2->GetTask().IsError())
                    {
                        Task2->EnsureCompletion();
                        return Task2->GetTask().Error();
                    }
                    DataObjectName = *Task2->GetTask().Result()->GetName();
                    Task2->EnsureCompletion();
                }
                {
                    auto Processing = true;
                    int32 ResponseCode;
                    FString ResponseBody("");
                    {
                        const auto Request = FHttpModule::Get().CreateRequest();
                        Request->OnProcessRequestComplete().BindLambda(
                            [&Processing, &ResponseCode, &ResponseBody](FHttpRequestPtr _, FHttpResponsePtr Response, bool Successful)
                            {
                                if (Successful) {
                                    ResponseCode = Response->GetResponseCode();
                                    ResponseBody = Response->GetContentAsString();
                                } else {
                                    ResponseCode = 999;
                                }
                                Processing = false;
                            }
                        );
                        Request->SetURL(Url);
                        Request->SetVerb(TEXT("PUT"));
                        Request->SetHeader("Content-Type", ContentType.IsSet() ? *ContentType : "application/octet-stream");
                        Request->SetContent(Binary);
                        Request->ProcessRequest();
                    }

                    if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
                    {
                        FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
                    }
                    else
                    {
                        while (Processing)
                        {
                            FPlatformProcess::Sleep(0.01f);
                        }
                    }

                    if (ResponseCode / 100 != 2)
                    {
                        const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                        return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
                }
                {
                    const auto Task = Self->Domain->DataObject(
                        DataObjectName
                    )->DoneUpload(
                        MakeShared<Gs2::Datastore::Request::FDoneUploadRequest>()
                    );
                    Task->StartSynchronousTask();
                    if (Task->GetTask().IsError())
                    {
                        Task->EnsureCompletion();
                        return Task->GetTask().Error();
                    }
                    *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                        Task->GetTask().Result(),
                        Self->GameSession,
                        Self->ConnectionValue
                    );
                    Task->EnsureCompletion();
                }
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FUploadTask>> FEzUserGameSessionDomain::Upload(
        TArray<uint8> Binary,
        TOptional<FString> Name,
        TOptional<FString> Scope,
        TOptional<FString> ContentType,
        TOptional<TArray<FString>> AllowUserIds,
        TOptional<bool> UpdateIfExists
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUploadTask>>(
            this->AsShared(),
            Binary,
            Name,
            Scope,
            ContentType,
            AllowUserIds,
            UpdateIfExists
        );
    }
    
    FEzUserGameSessionDomain::FDownloadTask::FDownloadTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString DataObjectId
    ): Self(Self), DataObjectId(DataObjectId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FDownloadTask::Action(
        TSharedPtr<TSharedPtr<TArray<uint8>>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                FString Url("");
                {
                    const auto Task = Self->Domain->PrepareDownload(
                        MakeShared<Gs2::Datastore::Request::FPrepareDownloadRequest>()
                            ->WithDataObjectId(DataObjectId)
                    );
                    Task->StartSynchronousTask();
                    if (Task->GetTask().IsError())
                    {
                        Task->EnsureCompletion();
                        return Task->GetTask().Error();
                    }
                    Url = *Task->GetTask().Result()->FileUrl;
                    Task->EnsureCompletion();
                }
                {
                    auto Processing = true;
                    int32 ResponseCode;
                    TArray<uint8> ResponseBody;
                    {
                        const auto request = FHttpModule::Get().CreateRequest();
                        request->OnProcessRequestComplete().BindLambda(
                            [&Processing, &ResponseCode, &ResponseBody](FHttpRequestPtr _, FHttpResponsePtr Response, bool Successful)
                            {
                                if (Successful) {
                                    ResponseCode = Response->GetResponseCode();
                                    ResponseBody = Response->GetContent();
                                } else {
                                    ResponseCode = 999;
                                }
                                Processing = false;
                            }
                        );
                        request->SetURL(Url);

                        request->SetVerb(TEXT("GET"));

                        request->ProcessRequest();
                    }

                    if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
                    {
                        FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
                    }
                    else
                    {
                        while (Processing)
                        {
                            FPlatformProcess::Sleep(0.01f);
                        }
                    }

                    if (ResponseCode / 100 != 2)
                    {
                        const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                        return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }

                    const auto Value = MakeShared<TArray<uint8>>();
                    Value->Append(ResponseBody);
                    *Result = Value;
                }
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FDownloadTask>> FEzUserGameSessionDomain::Download(
        FString DataObjectId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDownloadTask>>(
            this->AsShared(),
            DataObjectId
        );
    }
}
