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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Friend/Gs2Friend.h"
#include "Friend/Domain/Model/BlackListEntry.h"

namespace Gs2::Friend::Domain::Iterator
{

    class FDescribeBlackListIteratorLoadTask;

    class GS2FRIEND_API FDescribeBlackListIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Friend::Model::FBlackListEntry, FDescribeBlackListIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Friend::FGs2FriendRestClientPtr Client;

        friend FDescribeBlackListIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeBlackListIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeBlackListIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Friend::FGs2FriendRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2FRIEND_API IteratorImpl
        {
            friend FDescribeBlackListIterator;

            TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator::FNextTask>> Task;
            Gs2::Friend::Model::FBlackListEntryPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Friend::Model::FBlackListEntryPtr& operator*() const;
            Gs2::Friend::Model::FBlackListEntryPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeBlackListIterator> FDescribeBlackListIteratorPtr;

    class FDescribeBlackListIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FBlackListEntryPtr>>,
        public TSharedFromThis<FDescribeBlackListIteratorLoadTask>
    {
        TSharedPtr<FDescribeBlackListIterator> Self;

    public:
        explicit FDescribeBlackListIteratorLoadTask(
            TSharedPtr<FDescribeBlackListIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FBlackListEntryPtr>>> Result
        ) override;
    };
}
