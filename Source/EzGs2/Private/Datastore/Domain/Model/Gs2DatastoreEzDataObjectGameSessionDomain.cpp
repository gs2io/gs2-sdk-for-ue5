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

#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectGameSessionDomain.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    TOptional<FString> FEzDataObjectGameSessionDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzDataObjectGameSessionDomain::FileUrl() const
    {
        return Domain->FileUrl;
    }

    TOptional<int64> FEzDataObjectGameSessionDomain::ContentLength() const
    {
        return Domain->ContentLength;
    }

    TOptional<FString> FEzDataObjectGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzDataObjectGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDataObjectGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzDataObjectGameSessionDomain::DataObjectName() const
    {
        return Domain->DataObjectName;
    }

    FEzDataObjectGameSessionDomain::FEzDataObjectGameSessionDomain(
        Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzDataObjectGameSessionDomain::FUpdateDataObjectTask::FUpdateDataObjectTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self,
        TOptional<FString> Scope,
        TOptional<TArray<FString>> AllowUserIds
    ): Self(Self), Scope(Scope), AllowUserIds(AllowUserIds)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FUpdateDataObjectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FUpdateDataObjectTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Update(
                    MakeShared<Gs2::Datastore::Request::FUpdateDataObjectRequest>()
                        ->WithScope(Scope)
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
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FUpdateDataObjectTask>> FEzDataObjectGameSessionDomain::UpdateDataObject(
        TOptional<FString> Scope,
        TOptional<TArray<FString>> AllowUserIds
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateDataObjectTask>>(
            this->AsShared(),
            Scope,
            AllowUserIds
        );
    }

    FEzDataObjectGameSessionDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self,
        TOptional<FString> ContentType
    ): Self(Self), ContentType(ContentType)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FPrepareReUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FPrepareReUploadTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PrepareReUpload(
                    MakeShared<Gs2::Datastore::Request::FPrepareReUploadRequest>()
                        ->WithContentType(ContentType)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FPrepareReUploadTask>> FEzDataObjectGameSessionDomain::PrepareReUpload(
        TOptional<FString> ContentType
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareReUploadTask>>(
            this->AsShared(),
            ContentType
        );
    }

    FEzDataObjectGameSessionDomain::FDoneUploadTask::FDoneUploadTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FDoneUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FDoneUploadTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->DoneUpload(
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
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FDoneUploadTask>> FEzDataObjectGameSessionDomain::DoneUpload(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDoneUploadTask>>(
            this->AsShared()
        );
    }

    FEzDataObjectGameSessionDomain::FDeleteDataObjectTask::FDeleteDataObjectTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FDeleteDataObjectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FDeleteDataObjectTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Datastore::Request::FDeleteDataObjectRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FDeleteDataObjectTask>> FEzDataObjectGameSessionDomain::DeleteDataObject(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteDataObjectTask>>(
            this->AsShared()
        );
    }

    FEzDataObjectGameSessionDomain::FPrepareDownloadOwnDataTask::FPrepareDownloadOwnDataTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FPrepareDownloadOwnDataTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FPrepareDownloadOwnDataTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PrepareDownloadOwnData(
                    MakeShared<Gs2::Datastore::Request::FPrepareDownloadOwnDataRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FPrepareDownloadOwnDataTask>> FEzDataObjectGameSessionDomain::PrepareDownloadOwnData(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadOwnDataTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectHistoriesIteratorPtr FEzDataObjectGameSessionDomain::DataObjectHistories(
    ) const
    {
        return MakeShared<Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectHistoriesIterator>(
            Domain->DataObjectHistories(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzDataObjectGameSessionDomain::SubscribeDataObjectHistories(TFunction<void()> Callback)
    {
        return Domain->SubscribeDataObjectHistories(
            Callback
        );
    }

    void FEzDataObjectGameSessionDomain::UnsubscribeDataObjectHistories(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeDataObjectHistories(
            CallbackId
        );
    }

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryGameSessionDomainPtr FEzDataObjectGameSessionDomain::DataObjectHistory(
        const FString Generation
    ) const
    {
        return MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryGameSessionDomain>(
            Domain->DataObjectHistory(
                Generation
            ),
            ProfileValue
        );
    }

    FEzDataObjectGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectPtr> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FModelTask>> FEzDataObjectGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzDataObjectGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Datastore::Model::FEzDataObjectPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Datastore::Model::FDataObjectPtr Item)
            {
                Callback(Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Item));
            }
        );
    }

    void FEzDataObjectGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
    
    FEzDataObjectGameSessionDomain::FReUploadTask::FReUploadTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self,
        TArray<uint8> Binary,
        TOptional<FString> ContentType
    ): Self(Self), Binary(Binary), ContentType(ContentType)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FReUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FReUploadTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                FString Url("");
                {
                    const auto Task = Self->Domain->PrepareReUpload(
                        MakeShared<Gs2::Datastore::Request::FPrepareReUploadRequest>()
                    );
                    Task->StartSynchronousTask();
                    if (Task->GetTask().IsError())
                    {
                        Task->EnsureCompletion();
                        return Task->GetTask().Error();
                    }
                    Url = *Task->GetTask().Result()->GetUploadUrl();
                    Task->EnsureCompletion();
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
                    const auto Task = Self->Domain->DoneUpload(
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
                        Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FReUploadTask>> FEzDataObjectGameSessionDomain::ReUpload(
        TArray<uint8> Binary,
        TOptional<FString> ContentType
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReUploadTask>>(
            this->AsShared(),
            Binary
        );
    }

    FEzDataObjectGameSessionDomain::FDownloadTask::FDownloadTask(
        TSharedPtr<FEzDataObjectGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectGameSessionDomain::FDownloadTask::Action(
        TSharedPtr<TSharedPtr<TArray<uint8>>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FDownloadTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                FString Url("");
                {
                    const auto Task = Self->Domain->PrepareDownloadOwnData(
                        MakeShared<Gs2::Datastore::Request::FPrepareDownloadOwnDataRequest>()
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

    TSharedPtr<FAsyncTask<FEzDataObjectGameSessionDomain::FDownloadTask>> FEzDataObjectGameSessionDomain::Download(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDownloadTask>>(
            this->AsShared()
        );
    }
}
