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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "SerialKey/Domain/Iterator/DescribeSerialKeysIterator.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/User.h"

namespace Gs2::SerialKey::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSerialKeysIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeSerialKeys(
            MakeShared<Gs2::SerialKey::Request::FDescribeSerialKeysRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithCampaignModelName(Self->CampaignModelName)
                ->WithIssueJobName(Self->IssueJobName)
                ->WithPageToken(Self->PageToken)
                ->WithLimit(Self->FetchSize)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = R->GetItems();
        Self->PageToken = R->GetNextPageToken();
        Self->Last = !Self->PageToken.IsSet();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeSerialKeysIteratorLoadTask>>
    FDescribeSerialKeysIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeSerialKeysIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeSerialKeysIterator::FDescribeSerialKeysIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName,
        const TOptional<FString> IssueJobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        IssueJobName(IssueJobName),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::SerialKey::Model::FSerialKeyPtr& FDescribeSerialKeysIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::SerialKey::Model::FSerialKeyPtr FDescribeSerialKeysIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeSerialKeysIterator::IteratorImpl& FDescribeSerialKeysIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return *this;
    }

    FDescribeSerialKeysIterator::IteratorImpl FDescribeSerialKeysIterator::begin()
    {
        const auto Task = Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FDescribeSerialKeysIterator::IteratorImpl FDescribeSerialKeysIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

